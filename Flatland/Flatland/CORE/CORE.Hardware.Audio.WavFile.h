// CORE.Hardware.Audio.WavFile.h
////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
//#ifndef __CORE_HARDWARE_AUDIO_WAVFILE_
//#define __CORE_HARDWARE_AUDIO_WAVFILE_

#define MAKEDWORD(A,B,C,D) (((DWORD)(D)<<24) | ((DWORD)(C)<<16) | ((DWORD)(B)<<8) | (A))

class SOUNDINFO
{
public:
	bool Create(LPWAVEFORMATEX pFormat, LPBYTE pData, DWORD dwDataSize);
	LPWAVEFORMATEX GetWaveFormatEx();
	LPBYTE GetSoundData();
	void Release();
	SOUNDINFO();
	SOUNDINFO(HANDLE hFile);
	SOUNDINFO(LPCSTR lpszFilename);
	void init();

	bool IsValid();

	bool Load(HANDLE hFile);
	bool Load(LPCSTR lpszFilename);
	bool Save(HANDLE hFile);
	bool Save(LPCSTR lpszFilename);

	DWORD GetDataSize() { return m_dwDataSize; }

protected:
	bool m_bIsValid;
	WAVEFORMATEX m_waveFormatEx;
	LPBYTE m_pSoundData;
	DWORD m_dwDataSize;

private:
	bool LoadChunk(HANDLE hFile);
	bool LoadHeader(HANDLE hFile);
};

//#endif