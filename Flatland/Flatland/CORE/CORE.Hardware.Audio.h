// CORE.Hardware.Audio.h
//////////////////////////////////////////////////////////////////////

#pragma once
//#ifndef __CORE_HARDWARE_AUDIO_
//#define __CORE_HARDWARE_AUDIO_

#include "CORE.Hardware.Audio.WavFile.h"

void _InitializeDirectSound();
void _InitializeDirectSound(HWND hWnd, DWORD dwPriority=DSSCL_PRIORITY, LPGUID lpGuid=NULL);
void _ProcessDirectSoundEvents();
void _LoadSoundBank(int nBankNum);
void _ClearAllSoundBanks();
void _PlaySoundEffect(int nBankNum, int nSlotID, int option);
void _PlaySoundEffect(int nBankNum, int nSlotID);
void _StopSoundEffect(int nBankNum, int nSlotID);
void _SetSoundEffectVolume(int nBankNum, int nSlotID, float fVolume);
void _UninitializeDirectSound();

#define MAXSOUNDBANKS 10
#define MAXSOUNDSPERBANK 128
// How many times a given sound
// can be mixed over itself.
#define MIXINGFACTOR 8

#define NUMEVENTS 2
#define SOUNDEVENT_STARTED 24
#define SOUNDEVENT_FINISHED 42

#define BANK(N) N
#define SLOT(N) N

struct DEVICEDESC
{
	LPGUID lpGuid;
	char strDescription[64],
	strModule[64];
};

typedef DEVICEDESC *LPDEVICEDESC;
typedef void (*SOUND_EVENT_CALLBACK)(int nBankID, int nSlotID, DWORD dwEvent);

class SoundBank;
extern SoundBank g_SoundBanks[MAXSOUNDBANKS];
extern LPDIRECTSOUND m_pDirectSound;

#define SOUND_OPTION_NONE 0
#define SOUND_OPTION_NO_MIXING 1

class SoundBank  
{
public:
	SoundBank();
	virtual ~SoundBank();

	void Create(int nBankNum, SOUND_EVENT_CALLBACK func);
	int AddSound(SOUNDINFO *pWave, int nDup=0);
	bool SetFrequency(int nSound, int nFreq);
	bool PlaySound(int nSlotID);
	bool PlaySound(int nSlotID, int option);
	bool StopSound(int nSlotID);
	bool SetVolume(int nSlotID, float fVolume);

	// call during main loop
	void ProcessEvents();

	int GetNumSounds();
	void ReleaseSounds();

protected:
	int m_nBankNum;
	int m_nNumSounds;
	LPDIRECTSOUNDBUFFER m_ppSoundBuffer[MAXSOUNDSPERBANK][MIXINGFACTOR];
	DSBUFFERDESC m_pDSBufferDesc[MAXSOUNDSPERBANK];
	void Init();

	// Event utility functions
	BOOL InitEvents(DWORD dwSoundID, LPDSBUFFERDESC lpDSBufferDesc);
	BOOL DispatchEvent(int nBankID, int nSlotID, DWORD dwEvt);

	// Sound events and notifications
	LPDIRECTSOUNDNOTIFY  m_ppSoundNotify[MAXSOUNDSPERBANK][MIXINGFACTOR];
	DSBPOSITIONNOTIFY    m_ppDSBPosNotify[MAXSOUNDSPERBANK][NUMEVENTS];
	HANDLE               m_ppRGHEvent[MAXSOUNDSPERBANK][NUMEVENTS];
	SOUND_EVENT_CALLBACK m_pUserCallback;
};

//#endif
