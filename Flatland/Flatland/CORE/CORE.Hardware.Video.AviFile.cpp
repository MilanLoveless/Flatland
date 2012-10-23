// CORE.Hardware.Video.cpp
////////////////////////////////////////////////////////////////////////////////////////////

#include "../GameCore.h"

////////////////////////////////////////////////////////////////////////////////////////////

void CAviFile::BeginPlay(char *filename, HWND hWnd, bool bForward/*=true*/)
{
	VERIFY(Open(filename));
	BeginPlay(hWnd, bForward);
}

LPBITMAPINFO CAviFile::LockImageFrame() {
	
	//HDC hdc = GetDC(hWnd);

	//HDC hBmpDC = CreateCompatibleDC(hdc);
	//ASSERT(hBmpDC);
	LPBITMAPINFOHEADER pBmp;			// Decompressed video frame

	m_lNewTime = timeGetTime();
	m_lElapsedTime = m_lNewTime - m_lOldTime;
	m_lFrameTime += m_lElapsedTime * m_lVideoDirection;
	if(m_lFrameTime < 0 || m_lFrameTime > m_lVideoEndTime[0]) return NULL;

	GetVideoFrameAtTime(0, m_lFrameTime, &pBmp);

	LPBITMAPINFO pBmpInfo = (LPBITMAPINFO)pBmp;
	if(pBmpInfo != NULL) {
		//LPBYTE pBmpBits = ((LPBYTE)pBmpInfo) + pBmpInfo->bmiHeader.biSize;

		//SetDIBitsToDevice(hdc, rcDest.left, rcDest.top, pVideoFormat->bmiHeader.biWidth,
		//	pVideoFormat->bmiHeader.biHeight, 0, 0, 0, pVideoFormat->bmiHeader.biHeight,
		//	(LPVOID)pBmpBits, pBmpInfo, DIB_RGB_COLORS);
		
		m_lOldTime = m_lNewTime;
		//return pBmpBits;
		return pBmpInfo;
	}

	return NULL;

}

void CAviFile::UnlockImageFrame() {
	//PGETFRAME &pgf = m_pVideoPGF[0];
	//AVIStreamGetFrameClose(pgf);
}

void CAviFile::EndPlay() {
	//ReleaseDC(hWnd, hdc);
	VERIFY(EndVideoRetrieve(0));
	Release();
}

void CAviFile::BeginPlay(HWND hWnd, bool bForwards/*=true*/)
{
	VERIFY(StartVideoRetrieve(0));

	///////////////////////////
	// Calculate stuff for the main loop

	m_lFrameTime = bForwards?0:m_lVideoEndTime[0],// Millisecs into video clip
	m_lNewTime=0;						// Current time
	m_lOldTime=timeGetTime(),			// Time at last drawn frame
	m_lElapsedTime=0,					// Time between drawn frames
	m_lVideoDirection=bForwards?1:-1;	// 1=Forward -1=Reverse

	LPBITMAPINFO pVideoFormat =			// AVI File's video format
		GetVideoFormat(0);

	/////////////////////////////////////////////////////////////////

	RECT rcDest;						// Destination rect of video
	
	// (center the video in the display)
	{
		int nHalfWidth = (pVideoFormat->bmiHeader.biWidth >> 1),
			nHalfHeight = (pVideoFormat->bmiHeader.biHeight >> 1);
		
		rcDest.left = pVideoFormat->bmiHeader.biWidth - nHalfWidth;
		rcDest.top = pVideoFormat->bmiHeader.biHeight - nHalfHeight;
		rcDest.right = pVideoFormat->bmiHeader.biWidth + nHalfWidth;
		rcDest.bottom = pVideoFormat->bmiHeader.biHeight + nHalfHeight;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////
// Construction/Destruction
////////////////////////////////////////////////////////////////////////////////////////////

CAviFile::CAviFile()
{
	AVIFileInit();
	Init();
}

CAviFile::~CAviFile()
{
	AVIFileExit();
	Release();
}

void CAviFile::Init()
{
	m_pAviFile = NULL;
	m_nNumAudioStreams = 0;
	m_nNumVideoStreams = 0;

	int n;
	
	for(n = 0; n < MAX_AUDIO_STREAMS; n++)
	{
		m_pAudioStreams[n] = NULL;
		m_pAudioFormats[n] = NULL;
		m_pAudioData[n] = NULL;
	}

	for(n = 0; n < MAX_VIDEO_STREAMS; n++)
	{
		m_pVideoStreams[n] = NULL;
		m_pVideoFormats[n] = NULL;
		m_pVideoPGF[n] = NULL;
		m_lVideoEndTime[n] = 0;
	}
}

//
// The Release function must return the object's state to
// the way it was when it was initially allocated. The
// object must be ready to be reused.
//
void CAviFile::Release()
{
	if(m_pAviFile)
		AVIFileRelease(m_pAviFile);
	
	UINT n;
	for(n = 0; n < m_nNumAudioStreams; n++)
	{
		if(m_pAudioStreams[n])
			AVIStreamRelease(m_pAudioStreams[n]);

		if(m_pAudioFormats[n])
			delete [] ((LPBYTE)m_pAudioFormats[n]);

		if(m_pAudioData[n])
			delete [] m_pAudioData[n];
	}

	for(n = 0; n < m_nNumVideoStreams; n++)
	{
		if(m_pVideoStreams[n])
			AVIStreamRelease(m_pVideoStreams[n]);

		if(m_pVideoFormats[n])
			delete [] ((LPBYTE)m_pVideoFormats[n]);
	}

	Init();
}

bool CAviFile::Open(LPCSTR lpszFileName)
{
	if(AVIFileOpen(&m_pAviFile, lpszFileName, OF_READ, NULL))
		return false;

	FindStreams();
	
	if(!DetermineAudioFormats() ||
		!DetermineVideoFormats())
	{
		Release();
		return false;
	}

	// Okay, we know what's in the file.

	// Video and audio will be loaded as it's needed,
	// so there isn't a huge delay or impact on memory
	// when loading a large video file.

	// Yippee!
	return true;
}

void CAviFile::FindStreams()
{
	do
	{
		if(AVIFileGetStream(m_pAviFile, &m_pAudioStreams[m_nNumAudioStreams],
			streamtypeAUDIO, m_nNumAudioStreams))
			break;
	}
	while(++m_nNumAudioStreams < MAX_AUDIO_STREAMS);
	
	do
	{
		if(AVIFileGetStream(m_pAviFile, &m_pVideoStreams[m_nNumVideoStreams],
			streamtypeVIDEO, m_nNumVideoStreams))
			break;
	}
	while(++m_nNumVideoStreams < MAX_VIDEO_STREAMS);
}

bool CAviFile::DetermineAudioFormats()
{
	for(UINT n = 0; n < m_nNumAudioStreams; n++)
	{
		PAVISTREAM pStream = m_pAudioStreams[n];

		LONG lSize;
		if(AVIStreamReadFormat(pStream, AVIStreamStart(pStream), NULL, &lSize))
			return false;

		LPBYTE pChunk = new BYTE[lSize];
		if(!pChunk)
			return false;

		if(AVIStreamReadFormat(pStream, AVIStreamStart(pStream), pChunk, &lSize))
			return false;

		m_pAudioFormats[n] = (LPWAVEFORMAT)pChunk;
	}

	// Yay!
	return true;
}

bool CAviFile::DetermineVideoFormats()
{
	for(UINT n = 0; n < m_nNumVideoStreams; n++)
	{
		PAVISTREAM pStream = m_pVideoStreams[n];

		LONG lSize;
		if(AVIStreamReadFormat(pStream, AVIStreamStart(pStream), NULL, &lSize))
			return false;

		LPBYTE pChunk = new BYTE[lSize];
		if(!pChunk)
			return false;

		if(AVIStreamReadFormat(pStream, AVIStreamStart(pStream), pChunk, &lSize))
			return false;

		m_pVideoFormats[n] = (LPBITMAPINFO)pChunk;
	}

	// Bravo!
	return true;
}

int CAviFile::GetAudioStreamCount()
{
	return m_nNumAudioStreams;
}

int CAviFile::GetVideoStreamCount()
{
	return m_nNumVideoStreams;
}

LPBYTE CAviFile::ExtractAudioStream(UINT nStreamNum)
{
	if(m_pAudioData[nStreamNum])
		return m_pAudioData[nStreamNum];
	
	if(nStreamNum >= m_nNumAudioStreams)
		return NULL;

	PAVISTREAM pStream = m_pAudioStreams[nStreamNum];

	LONG lSize;
	if(AVIStreamRead(pStream, 0, AVISTREAMREAD_CONVENIENT, NULL, 0, &lSize, NULL))
		return NULL;

	LPBYTE pBuffer = new BYTE[lSize];
	if(!pBuffer)
		return NULL;

	if(AVIStreamRead(pStream, 0, AVISTREAMREAD_CONVENIENT, pBuffer, lSize, NULL, NULL))
		return NULL;

	m_pAudioData[nStreamNum] = pBuffer;

	return pBuffer;
}

bool CAviFile::StartVideoRetrieve(UINT nStreamNum)
{
	if(nStreamNum >= m_nNumVideoStreams)
		return false;

	PAVISTREAM pStream = m_pVideoStreams[nStreamNum];


	PGETFRAME &pgf = m_pVideoPGF[nStreamNum];
	LPBITMAPINFOHEADER lpDesiredFormat = &m_pVideoFormats[nStreamNum]->bmiHeader;
	
	pgf = AVIStreamGetFrameOpen(pStream, NULL /*lpDesiredFormat*/);

	if(!pgf)
		return false;

	m_lVideoEndTime[nStreamNum] = AVIStreamEndTime(pStream);
	AVIStreamBeginStreaming(pStream, 0, AVIStreamLength(pStream), 1000);

	// Yahoo!
	return true;
}

bool CAviFile::EndVideoRetrieve(UINT nStreamNum)
{
	PAVISTREAM pStream = m_pVideoStreams[nStreamNum];
	AVIStreamEndStreaming(pStream);

	PGETFRAME &pgf = m_pVideoPGF[nStreamNum];

	if(AVIStreamGetFrameClose(pgf))
		return false;

	pgf = NULL;

	// Hurray!
	return true;
}

void CAviFile::GetVideoFrameAtTime(UINT nStreamNum, LONG lTimeInMilliSec, LPBITMAPINFOHEADER *ppbi)
{
	if(nStreamNum >= m_nNumVideoStreams)
	{
		*ppbi = NULL;
		return;
	}

	PAVISTREAM pStream = m_pVideoStreams[nStreamNum];
	PGETFRAME &pgf = m_pVideoPGF[nStreamNum];

	LONG lFrame;
	if(lTimeInMilliSec <= m_lVideoEndTime[nStreamNum])
		lFrame = AVIStreamTimeToSample(pStream, lTimeInMilliSec);
	else
	{
		*ppbi = NULL; // video is done, no more frames
		return;
	}

	*ppbi = (LPBITMAPINFOHEADER)AVIStreamGetFrame(pgf, lFrame);
}

void CAviFile::GetVideoFrame(UINT nStreamNum, LONG lFrame, LPBITMAPINFOHEADER *ppbi)
{
	PGETFRAME &pgf = m_pVideoPGF[nStreamNum];
	*ppbi = (LPBITMAPINFOHEADER)AVIStreamGetFrame(pgf, lFrame);
	// NULL on error or no more frames
}

LPWAVEFORMAT CAviFile::GetAudioFormat(UINT nStreamNum)
{
	if(nStreamNum >= m_nNumAudioStreams)
		return NULL;

	return m_pAudioFormats[nStreamNum];
}

LPBITMAPINFO CAviFile::GetVideoFormat(UINT nStreamNum)
{
	if(nStreamNum >= m_nNumVideoStreams)
		return NULL;

	return m_pVideoFormats[nStreamNum];
}
