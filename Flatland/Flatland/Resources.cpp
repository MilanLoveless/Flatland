// GameCore.Extras.cpp
////////////////////////////////////////////////////////////////////////////////////////////

#include "GameCore.h"

////////////////////////////////////////////////////////////////////////////////////////////

HCURSOR _GetAppCursor(int nID) {
	switch(nID) {
	case -1:
		return LoadCursor(NULL, IDC_ARROW);
		break;
	case 0:
		return LoadCursor(NULL, IDC_ARROW);
		// Hardware custom mouse cursors (Example...)
		//return (HCURSOR)LoadImage(g_hInstance, MAKEINTRESOURCE(IDC_GAMECORE_CURSOR), IMAGE_CURSOR, 32, 32, 0);
		break;
	}
}

SOUNDINFO* _GetAppSound(int nBankID, int nSoundID) {
	if(nBankID == 0) {
		switch(nSoundID) {
		case 0:
			return new SOUNDINFO("RESOURCES/SOUNDS OF FLATLAND/bag-crunch-1.wav");
			break;
		case 1:
			return new SOUNDINFO("RESOURCES/SOUNDS OF FLATLAND/bag-rustle-1.wav");
			break;
		case 2:
			return new SOUNDINFO("RESOURCES/SOUNDS OF FLATLAND/foil-crunch-1.wav");
			break;
		case 3:
			return new SOUNDINFO("RESOURCES/SOUNDS OF FLATLAND/foil-rip-1.wav");
			break;
		case 4:
			return new SOUNDINFO("RESOURCES/SOUNDS OF FLATLAND/foil-tear-1.wav");
			break;
		case 5:
			return new SOUNDINFO("RESOURCES/SOUNDS OF FLATLAND/step-1.wav");
			break;
		case 6:
			return new SOUNDINFO("RESOURCES/SOUNDS OF FLATLAND/step-2.wav");
			break;
		case 7:
			return new SOUNDINFO("RESOURCES/SOUNDS OF FLATLAND/step-3.wav");
			break;
		case 8:
			return new SOUNDINFO("RESOURCES/SOUNDS OF FLATLAND/step-4.wav");
			break;
		case 9:
			return new SOUNDINFO("RESOURCES/SOUNDS OF FLATLAND/step-5.wav");
			break;
		case 10:
			return new SOUNDINFO("RESOURCES/SOUNDS OF FLATLAND/flatland-bgm.wav");
			break;
		case 11:
			return new SOUNDINFO("RESOURCES/SOUNDS OF FLATLAND/fire-1.wav");
			break;
		}
	}
	return NULL;
}

void _OnAppSoundEvent(int nBankID, int nSlotID, int dwEvent) {
	if(dwEvent == SOUNDEVENT_STARTED) {
		// Detect when given sound effect starts
	}
	if(dwEvent == SOUNDEVENT_FINISHED) {
		// Detect when given sound effect finishes
	}
}

void _OnWindowsMessage(HWND hWindow, UINT uMessage, WPARAM wParam, LPARAM lParam) {
	// (Advanced: Handle windows event messages)
	switch(uMessage)
    {
    case WM_LBUTTONUP:
		// Play sound effect on click (Example...)
		//_PlaySoundEffect(BANK(0), SLOT(0));
        break;
    }
}