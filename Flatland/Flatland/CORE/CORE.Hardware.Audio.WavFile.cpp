// CORE.Hardware.Audio.WavFile.cpp
/////////////////////////////////////////////////////////////////////////////////////////////////

#include "../GameCore.h"

SOUNDINFO::SOUNDINFO()
{
	init();
}

SOUNDINFO::SOUNDINFO(HANDLE hFile)
{
	init();
	m_bIsValid = Load(hFile);
	ASSERT(m_bIsValid);
}

SOUNDINFO::SOUNDINFO(LPCSTR lpszFilename)
{
	init();
	m_bIsValid = Load(lpszFilename);
	ASSERT(m_bIsValid);
}

void SOUNDINFO::init()
{
	m_bIsValid = false;
	m_dwDataSize = 0;
	memset(&m_waveFormatEx, 0, sizeof(WAVEFORMATEX));
	m_pSoundData = NULL;
}

bool SOUNDINFO::IsValid()
{
	return m_bIsValid;
}

bool SOUNDINFO::Load(HANDLE hFile)
{
	if(LoadHeader(hFile))
	{
		while(LoadChunk(hFile));
		if(m_pSoundData) m_bIsValid = true;
		return true;
	}
	
	return false;
}

bool SOUNDINFO::Load(LPCSTR lpszFilename)
{
	HANDLE hFile = CreateFile(lpszFilename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile == INVALID_HANDLE_VALUE)
	{
		ASSERT(false);
		return false;
	}

	bool bRet = Load(hFile);
	CloseHandle(hFile);
	return bRet;
}

bool SOUNDINFO::Save(HANDLE hFile)
{
	return false;
}

bool SOUNDINFO::Save(LPCSTR lpszFilename)
{
	HANDLE hFile = CreateFile(lpszFilename, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile == INVALID_HANDLE_VALUE)
	{
		ASSERT(false);
		return false;
	}

	bool bRet = Save(hFile);
	CloseHandle(hFile);
	return bRet;
}

bool SOUNDINFO::LoadHeader(HANDLE hFile)
{
	const int nHeaderSize = 12;
	DWORD pHeader[nHeaderSize / sizeof(DWORD)];
	DWORD dwNumRead;
	ReadFile(hFile, pHeader, nHeaderSize, &dwNumRead, NULL);
	if(*pHeader == MAKEDWORD('R','I','F','F')) return true;
	return false;
}

bool SOUNDINFO::LoadChunk(HANDLE hFile)
{
	LPBYTE pJunk;
	DWORD dwNumRead;

	/*MMCKINFO ck;
	ReadFile(hFile, &ck, sizeof(MMCKINFO), &dwNumRead, NULL);
	if(dwNumRead != sizeof(MMCKINFO)) return false;*/

	struct { DWORD ckid, ckSize; } ck;
	ReadFile(hFile, &ck, sizeof(ck), &dwNumRead, NULL);
	if(dwNumRead != sizeof(ck)) return false;

	switch(ck.ckid)
	{
	case MAKEDWORD('f','m','t',' '):
		ReadFile(hFile, &m_waveFormatEx, sizeof(PCMWAVEFORMAT), &dwNumRead, NULL);
		if(dwNumRead != sizeof(PCMWAVEFORMAT)) { Release(); return false; }
		pJunk = new BYTE[ck.ckSize - dwNumRead];
		ReadFile(hFile, pJunk, ck.ckSize - dwNumRead, &dwNumRead, NULL);
		m_waveFormatEx.cbSize = sizeof(WAVEFORMATEX);
		delete [] pJunk;
		break;
	case MAKEDWORD('d','a','t','a'):
		m_dwDataSize = ck.ckSize;
		m_pSoundData = new BYTE[m_dwDataSize];
		if(!m_pSoundData) return false;
		
		ReadFile(hFile, m_pSoundData, m_dwDataSize, &dwNumRead, NULL);
		if(dwNumRead != m_dwDataSize) { Release(); return false; }
		break;
	default: // unknown chunk - ignore
		pJunk = new BYTE[ck.ckSize];
		ReadFile(hFile, pJunk, ck.ckSize, &dwNumRead, NULL);
		delete [] pJunk;
		if(dwNumRead != ck.ckSize) return false;
		break;
	}

	return true;
}

void SOUNDINFO::Release()
{
	if(m_dwDataSize) delete [] m_pSoundData;
	m_dwDataSize = 0;
	m_bIsValid = 0;
	memset(&m_waveFormatEx, 0, sizeof(WAVEFORMATEX));
}

LPBYTE SOUNDINFO::GetSoundData()
{
	return m_pSoundData;
}

LPWAVEFORMATEX SOUNDINFO::GetWaveFormatEx()
{
	if(!m_bIsValid) return false;
	return &m_waveFormatEx;
}

bool SOUNDINFO::Create(LPWAVEFORMATEX pFormat, LPBYTE pData, DWORD dwDataSize)
{
	ASSERT(pFormat);
	ASSERT(pData);
	memcpy(&m_waveFormatEx, pFormat, sizeof(WAVEFORMATEX));
	m_pSoundData = pData;
	m_dwDataSize = dwDataSize;
	m_bIsValid = true;
	return true;
}
