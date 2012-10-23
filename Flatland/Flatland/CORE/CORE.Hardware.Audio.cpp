// CORE.Hardware.Audio.cpp
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "../GameCore.h"

int g_nNumDevices = 0;
SoundBank g_SoundBanks[MAXSOUNDBANKS];
LPDIRECTSOUND g_pDirectSound = NULL;
void _SoundEventHandler(int nBankID, int nSlotID, DWORD dwEvent);

///////////////////////////////////////////////////////////////////////////////////////////////////
// Main Interface
///////////////////////////////////////////////////////////////////////////////////////////////////

void _InitializeDirectSound() {
	_InitializeDirectSound(g_hMainWnd, DSSCL_PRIORITY, NULL);
	for(int nBankNum = 0; nBankNum < MAXSOUNDBANKS; nBankNum++) {
		g_SoundBanks[nBankNum].Create(nBankNum, _SoundEventHandler);
	}
}

void _InitializeDirectSound(HWND hWnd, DWORD dwPriority/*=DSSCL_PRIORITY*/, LPGUID lpGuid/*=NULL*/)
{
	VERIFY( DirectSoundCreate(lpGuid, &g_pDirectSound, NULL) );
	if(g_pDirectSound == NULL) return;
	VERIFY( g_pDirectSound->SetCooperativeLevel(hWnd, dwPriority) );
}

void _UninitializeDirectSound() {
	_ClearAllSoundBanks();
	if(g_pDirectSound) g_pDirectSound->Release();
	g_pDirectSound = NULL;
}

void _ClearAllSoundBanks() {
	for(int n = 0; n < MAXSOUNDBANKS; n++) {
		g_SoundBanks[n].ReleaseSounds();
	}
}

void _SoundEventHandler(int nBankID, int nSlotID, DWORD dwEvent) {
	return _OnAppSoundEvent(nBankID, nSlotID, dwEvent);
}

void _LoadSoundBank(int nBankNum) {
	SOUNDINFO *pSound = NULL;
	int nSlotNum = 0;
	while((pSound = _GetAppSound(nBankNum, nSlotNum)) != NULL) {
		g_SoundBanks[nBankNum].AddSound(pSound);
		nSlotNum++;
	}
}

void _PlaySoundEffect(int nBankNum, int nSlotID) {
	_PlaySoundEffect(nBankNum, nSlotID, SOUND_OPTION_NONE);
}

void _PlaySoundEffect(int nBankNum, int nSlotID, int option) {
	g_SoundBanks[nBankNum].PlaySound(nSlotID, option);
}

void _StopSoundEffect(int nBankNum, int nSlotID) {
	g_SoundBanks[nBankNum].StopSound(nSlotID);
}

void _SetSoundEffectVolume(int nBankNum, int nSlotID, float fVolume) {
	if(fVolume < 0.0) fVolume = 0.0;
	if(fVolume > 1.0) fVolume = 1.0;
	g_SoundBanks[nBankNum].SetVolume(nSlotID, fVolume);
}

void _ProcessDirectSoundEvents() {
	for(int n = 0; n < MAXSOUNDBANKS; n++) {
		g_SoundBanks[n].ProcessEvents();
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Device Enumeration
///////////////////////////////////////////////////////////////////////////////////////////////////
BOOL CALLBACK DSEnumCallback(LPGUID lpGuid, LPCSTR lpcstrDescription, LPCSTR lpcstrModule, LPVOID lpContext)
{
	LPDEVICEDESC pDeviceDesc = (LPDEVICEDESC)lpContext;
	ASSERT(pDeviceDesc);
	pDeviceDesc[g_nNumDevices].lpGuid = lpGuid;
	strcpy(pDeviceDesc[g_nNumDevices].strDescription, lpcstrDescription);
	strcpy(pDeviceDesc[g_nNumDevices].strModule, lpcstrModule);
	g_nNumDevices++;
	return TRUE;
}

int _DetectDevices(LPDEVICEDESC pDeviceDesc)
{
	ASSERT(pDeviceDesc);
	VERIFY(	DirectSoundEnumerate(DSEnumCallback, pDeviceDesc) );
	return g_nNumDevices;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Error Handling
///////////////////////////////////////////////////////////////////////////////////////////////////
void ProcessResultA(HRESULT hResult, LPSTR strFile, int nLine)
{
	char strMessage[255];
	switch(hResult)
	{
		case DSERR_ALLOCATED: strcpy(strMessage, "The request failed because resources, such as a priority level, were already in use by another caller."); break;
		case DSERR_ALREADYINITIALIZED: strcpy(strMessage, "The object is already initialized."); break;
		case DSERR_BADFORMAT: strcpy(strMessage, "The specified wave format is not supported."); break;
		case DSERR_BUFFERLOST: strcpy(strMessage, "The buffer memory has been lost and must be restored."); break;
		case DSERR_CONTROLUNAVAIL: strcpy(strMessage, "The control (volume, pan, and so forth) requested by the caller is not available."); break;
		case DSERR_GENERIC: strcpy(strMessage, "An undetermined error occurred inside the DirectSound subsystem."); break;
		case DSERR_INVALIDCALL: strcpy(strMessage, "This function is not valid for the current state of this object."); break;
		case DSERR_INVALIDPARAM: strcpy(strMessage, "An invalid parameter was passed to the returning function."); break;
		case DSERR_NOAGGREGATION: strcpy(strMessage, "The object does not support aggregation."); break;
		case DSERR_NODRIVER: strcpy(strMessage, "No sound driver is available for use."); break;
		case DSERR_NOINTERFACE: strcpy(strMessage, "The requested COM interface is not available."); break;
		case DSERR_OTHERAPPHASPRIO: strcpy(strMessage, "Another application has a higher priority level, preventing this call from succeeding"); break;
		case DSERR_OUTOFMEMORY: strcpy(strMessage, "The DirectSound subsystem could not allocate sufficient memory to complete the caller's request."); break;
		case DSERR_PRIOLEVELNEEDED: strcpy(strMessage, "The caller does not have the priority level required for the function to succeed."); break;
		case DSERR_UNINITIALIZED: strcpy(strMessage, "The IDirectSound::Initialize method has not been called or has not been called successfully before other methods were called."); break;
		case DSERR_UNSUPPORTED: strcpy(strMessage, "The function called is not supported at this time."); break;
		default: strcpy(strMessage, "An unknown error has occured."); break;
	}

	::MessageBeep(MB_ICONEXCLAMATION);
	::MessageBox(NULL, strMessage, "CORE Hardware Audio", MB_OK | MB_ICONEXCLAMATION);

	PostQuitMessage(1);
}

///////////////////////////////////////////////////////////////////////////////////////////////////
// Sound Bank
///////////////////////////////////////////////////////////////////////////////////////////////////

SoundBank::SoundBank()
{
	Init();
}

SoundBank::~SoundBank()
{
	ReleaseSounds();
}

void SoundBank::Init()
{
	m_nBankNum = 0;
	m_nNumSounds = 0;
	m_pUserCallback = NULL;
	for(int n = 0; n < MAXSOUNDSPERBANK; n++) {
		for(int m = 0; m < MIXINGFACTOR; m++) {
			m_ppSoundBuffer[n][m] = NULL;
			m_ppSoundNotify[n][m] = NULL;
		}
		ZeroMemory(&m_pDSBufferDesc[n], sizeof(m_pDSBufferDesc[n]));
		for(int m = 0; m < NUMEVENTS; m++) {
			ZeroMemory(&m_ppDSBPosNotify[n][m], sizeof(m_ppDSBPosNotify[n][m]));
			m_ppRGHEvent[n][m] = NULL;
		}
	}
}

void SoundBank::ReleaseSounds()
{
	for(int n = 0; n < m_nNumSounds; n++)
	{
		for(int m = 0; m < MIXINGFACTOR; m++) {
			if(m_ppSoundBuffer[n][m] != NULL) { m_ppSoundBuffer[n][m]->Release(); }
			if(m_ppSoundNotify[n][m] != NULL) { m_ppSoundNotify[n][m]->Release(); }
		}
	}

	Init();
}

//////////////////////////////////////////////////////////////////////
// Main Usage
//////////////////////////////////////////////////////////////////////

void SoundBank::Create(int nBankNum, SOUND_EVENT_CALLBACK func) {
	Init();
	m_nBankNum = nBankNum;
	m_pUserCallback = func;
}

int SoundBank::AddSound(SOUNDINFO *pWave, int nDup/*=0*/)
{
	if(!pWave || !pWave->IsValid()) return -1;
	DSBUFFERDESC desc;
	memset(&desc, 0, sizeof(DSBUFFERDESC));
	desc.dwSize = sizeof(DSBUFFERDESC);
	desc.dwFlags =
            DSBCAPS_GETCURRENTPOSITION2
            | DSBCAPS_GLOBALFOCUS
            | DSBCAPS_CTRLPOSITIONNOTIFY
			| DSBCAPS_CTRLVOLUME;
 
	desc.dwBufferBytes = pWave->GetDataSize();
	desc.lpwfxFormat = pWave->GetWaveFormatEx();
 
	VERIFY(
		g_pDirectSound->CreateSoundBuffer(&desc, &m_ppSoundBuffer[m_nNumSounds][0], NULL)
	);

	// SECTION TWO: Write information -
	LPBYTE pData;
	DWORD nDataSize;

	VERIFY(
		m_ppSoundBuffer[m_nNumSounds][0]->Lock(0, pWave->GetDataSize(), (void**)(&pData), &nDataSize, NULL, 0, 0)
	);

	memcpy(pData, pWave->GetSoundData(), nDataSize);

	VERIFY(
		m_ppSoundBuffer[m_nNumSounds][0]->Unlock(pData, nDataSize, NULL, 0)
	);

	// Save a copy of a buffer description
	memcpy(&m_pDSBufferDesc[m_nNumSounds], &desc, sizeof(desc));

	// Create sub-slots to allow the same sound to be overlapped
	LPDIRECTSOUNDBUFFER p = m_ppSoundBuffer[m_nNumSounds][0];
	for(int n = 1; n < MIXINGFACTOR; n++) {
		// NOTE: This only duplicates meta-data not the sound buffer itself
		g_pDirectSound->DuplicateSoundBuffer(p, &m_ppSoundBuffer[m_nNumSounds][n]);
	}

	// Initialize events for the new sound
	InitEvents(m_nNumSounds, &desc);

	return m_nNumSounds++;
}

bool SoundBank::PlaySound(int nSlotID)
{
	PlaySound(nSlotID, SOUND_OPTION_NONE);
}

bool SoundBank::PlaySound(int nSlotID, int option)
{
	DWORD position;
	ASSERT(g_pDirectSound);
	ASSERT(m_ppSoundBuffer[nSlotID][0]);
	ASSERT(nSlotID < m_nNumSounds);
	// find the next available sub-slot if one exists
	int nMixingFactor = MIXINGFACTOR;
	if(option & SOUND_OPTION_NO_MIXING) {
		nMixingFactor = 1;
	}
	for(int nSubSlotID = 0; nSubSlotID < nMixingFactor; nSubSlotID++) {
		m_ppSoundBuffer[nSlotID][nSubSlotID]->GetCurrentPosition(&position, NULL);
		if(position == 0) {
			VERIFY(
				m_ppSoundBuffer[nSlotID][nSubSlotID]->Play(0,0,0)
			);
			// Only play one available buffer.
			break;
		}
	}
	return true;
}

bool SoundBank::StopSound(int nSlotID) {
	DWORD position;
	ASSERT(g_pDirectSound);
	ASSERT(m_ppSoundBuffer[nSlotID][0]);
	ASSERT(nSlotID < m_nNumSounds);
	for(int nSubSlotID = 0; nSubSlotID < MIXINGFACTOR; nSubSlotID++) {
		m_ppSoundBuffer[nSlotID][nSubSlotID]->GetCurrentPosition(&position, NULL);
		if(position != 0) {
			VERIFY(
				m_ppSoundBuffer[nSlotID][nSubSlotID]->Stop()
			);
		}
	}
	return true;
}

bool SoundBank::SetVolume(int nSlotID, float fVolume) 
{
	if(fVolume < 0.0) fVolume = 0.0;
	if(fVolume > 1.0) fVolume = 1.0;
	DWORD position;
	ASSERT(g_pDirectSound);
	ASSERT(m_ppSoundBuffer[nSlotID][0]);
	ASSERT(nSlotID < m_nNumSounds);
	LONG lVolume = DSBVOLUME_MIN/2.5 + fVolume * (DSBVOLUME_MAX - DSBVOLUME_MIN/2.5);
	for(int nSubSlotID = 0; nSubSlotID < MIXINGFACTOR; nSubSlotID++) {
		m_ppSoundBuffer[nSlotID][nSubSlotID]->GetCurrentPosition(&position, NULL);
		if(position != 0) {
			VERIFY(
				m_ppSoundBuffer[nSlotID][nSubSlotID]->SetVolume(lVolume)
			);
		}
	}
	return true;
}


bool SoundBank::SetFrequency(int nSlotID, int nFreq)
{
	ASSERT(g_pDirectSound);
	for(int nSubSlotID = 0; nSubSlotID < MIXINGFACTOR; nSubSlotID++) {
		ASSERT(m_ppSoundBuffer[nSlotID][nSubSlotID]);
		VERIFY(
			m_ppSoundBuffer[nSlotID][nSubSlotID]->SetFrequency(nFreq)
		);
	}

	return true;
}

//////////////////////////////////////////////////////////////////////
// Event Processing
//////////////////////////////////////////////////////////////////////
void SoundBank::ProcessEvents()
{
	// This code is based on Microsoft's Documentation

	for(int n = 0; n < m_nNumSounds; n++)
	{
		DWORD dwEvt = MsgWaitForMultipleObjects(
		        NUMEVENTS,      // How many possible events
			    m_ppRGHEvent[n],// Location of handles
				FALSE,          // Wait for all?
	            0,				// How long to wait
		        QS_ALLINPUT);   // Any message is an event
	
	    // WAIT_OBJECT_0 == 0 but is properly treated as an arbitrary
		// index value assigned to the first event, therefore I subtract
	    // it from dwEvt to get the zero-based index of the event.
 
		dwEvt -= WAIT_OBJECT_0;
 
	    // If the event was set by the buffer, there's input
		// to process. 
 
	    if (dwEvt < NUMEVENTS) {
		    DispatchEvent(m_nBankNum, n, dwEvt);
		}
 
		// If it's the last event, it's a regular windows message
	}
}

BOOL SoundBank::DispatchEvent(int nBankID, int nSlotID, DWORD dwEvt)
{
	if(m_pUserCallback == NULL) {
		return TRUE;
	}

	// Check which event index we asked for is being triggered
	switch(dwEvt) {
	case 0:
		// This was configured to trigger when the sound starts playing
		m_pUserCallback(nBankID, nSlotID, SOUNDEVENT_STARTED);
		break;
	case 1:
		// This was configured to trigger when the sound finishes playing
		m_pUserCallback(nBankID, nSlotID, SOUNDEVENT_FINISHED);
		break;
	}
	
	/*
	// This code is based on Microsoft's Documentation

	LONG            lNumToWrite;
    DWORD           dwStartOfs;
    //VOID            *lpvPtr1, *lpvPtr2;
    //DWORD           dwBytes1, dwBytes2;
    //UINT            cbBytesRead;
    static DWORD    dwStopNextTime = 0xFFFF;
 
    if (dwStopNextTime == dwEvt)   // All data has been played
    {
		ASSERT(m_ppSoundBuffer[nSlotID]);
        m_ppSoundBuffer[nSlotID]->Stop();
        dwStopNextTime = 0xFFFF;

		// notify user
		if(m_pUserCallback) {
			m_pUserCallback(nBankID, nSlotID, SOUNDEVENT_FINISHED);
		}

        return TRUE;
    }
 
    if (dwStopNextTime != 0xFFFF)
        return TRUE;
 
	if (dwEvt == 0)
        dwStartOfs = m_ppDSBPosNotify[nSlotID][NUMEVENTS - 1].dwOffset;
    else
        dwStartOfs = m_ppDSBPosNotify[nSlotID][dwEvt-1].dwOffset;
 
	lNumToWrite = (LONG) m_ppDSBPosNotify[nSlotID][dwEvt].dwOffset - dwStartOfs;
    if (lNumToWrite < 0) lNumToWrite += m_pDSBufferDesc[nSlotID].dwBufferBytes;
	*/

	return TRUE;
}

BOOL SoundBank::InitEvents(DWORD dwSoundID, LPDSBUFFERDESC lpDSBufferDesc)
{
	// Initialize all events for the sound ID specified.
	// Called when sound is added to object.

    for(int i = 0; i < NUMEVENTS; i++)
    {
        m_ppRGHEvent[dwSoundID][i] = CreateEvent(NULL, FALSE, FALSE, NULL);
        if (NULL == m_ppRGHEvent[dwSoundID][i]) return FALSE;
    }

	// This will set notification to trigger index 0 when the sound starts 
    m_ppDSBPosNotify[dwSoundID][0].dwOffset = 0;
    m_ppDSBPosNotify[dwSoundID][0].hEventNotify = m_ppRGHEvent[dwSoundID][0];

	// This will set notification to trigger index 1 when sound ends (even when stopped manually)
    m_ppDSBPosNotify[dwSoundID][1].dwOffset = DSBPN_OFFSETSTOP;
    m_ppDSBPosNotify[dwSoundID][1].hEventNotify = m_ppRGHEvent[dwSoundID][1];

	for(int nSubSlotID = 0; nSubSlotID < MIXINGFACTOR; nSubSlotID++) {
		// Build a IDirectSoundNotify object for this sound buffer 
		if FAILED(IDirectSoundBuffer_QueryInterface(m_ppSoundBuffer[dwSoundID][nSubSlotID], 
				IID_IDirectSoundNotify, (VOID **)&m_ppSoundNotify[dwSoundID][nSubSlotID]))
			return FALSE; 
 
		if FAILED(IDirectSoundNotify_SetNotificationPositions(
				 m_ppSoundNotify[dwSoundID][nSubSlotID], NUMEVENTS, m_ppDSBPosNotify[dwSoundID]))
		{
			IDirectSoundNotify_Release(m_ppSoundNotify[dwSoundID][nSubSlotID]);
			return FALSE;
		}
	}

	return TRUE;
}