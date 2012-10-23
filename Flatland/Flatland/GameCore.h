#ifndef _FLATLAND
#define _FLATLAND

#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <MMSYSTEM.h>
#include <dsound.h>

#include <stdio.h>

using namespace std;

#include "CORE/CORE.Animation.h"
#include "CORE/CORE.Collection.h"
#include "CORE/CORE.Debugging.h"
#include "CORE/CORE.Hardware.3D.h"
#include "CORE/CORE.Hardware.Audio.h"
#include "CORE/CORE.Hardware.Audio.WavFile.h"
#include "CORE/CORE.Hardware.Drawing.3D.h"
#include "CORE/CORE.Hardware.Video.AviFile.h"
#include "CORE/CORE.Image.h"
#include "CORE/CORE.Keyboard.h"
#include "CORE/CORE.Mouse.h"
#include "CORE/CORE.Software.Drawing.2D.h"
#include "CORE/CORE.Windows.h"
#include "Draw.h"

#include "resource.h"
#include "Constants.h"
#include "Rect.h"

HCURSOR _GetAppCursor(int nID);
SOUNDINFO* _GetAppSound(int nBankID, int nSoundID);
void _OnAppSoundEvent(int nBankID, int nSlotID, int dwEvent);
void _OnWindowsMessage(HWND hWindow, UINT uMessage, WPARAM wParam, LPARAM lParam);
void _OnInitialize();
void _OnUninitialize();
void _OnFrame();
void ShowMenu();
void ShowGame(int level);
void ShowGameOver();
void ShowEnding();

#endif //_FLATLAND