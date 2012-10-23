// CORE.Windows.cpp
//////////////////////////////////////////////////////////////////////////////////////////////////

#include "../GameCore.h"

HINSTANCE g_hInstance;
HWND g_hMainWnd;
BOOL g_bAppRunning;
char* g_strWindowCaption = "GameCore";

void _SetWindowCaption(char *str) {
	g_strWindowCaption = str;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	g_hInstance = hInstance;
    g_bAppRunning = true;

	_OnInitInstance(hInstance);

	Keyboard::_Initialize();

	_Initialize_CORE_Debug();

    _InitializeDirect3D(0, 0, D3DFMT_A8R8G8B8, g_hMainWnd, true);
	_InitializeDirectSound();

	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = WINDOW_WIDTH;
	rect.bottom = WINDOW_HEIGHT;
	_InitializeCOREDrawing3D(&rect);

	_OnInitialize();

    MSG msg;
    while(g_bAppRunning)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

		_ProcessDirectSoundEvents();
		_OnFrame();
    }

	_OnUninitialize();

	_UninitializeCOREDrawing3D();

	_UninitializeDirectSound();
    _UninitializeDirect3D();

	_Uninitialize_CORE_Debug();

    return 0;
}

LRESULT CALLBACK _WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	_OnWindowsMessage(hWnd, uMessage, wParam, lParam);

	switch(uMessage)
    {
	case WM_KEYDOWN:
		Keyboard::_SetKeyboardKey((UINT)wParam, true);
		break;

	case WM_KEYUP:
		Keyboard::_SetKeyboardKey((UINT)wParam, false);
		break;

	case WM_LBUTTONDOWN:
        Mouse::_SetMousePosition(MAKEPOINTS(lParam).x, MAKEPOINTS(lParam).y);
        Mouse::_SetMouseLeftButton(true);
        break;	

    case WM_LBUTTONUP:
        Mouse::_SetMousePosition(MAKEPOINTS(lParam).x, MAKEPOINTS(lParam).y);
        Mouse::_SetMouseLeftButton(false);
        break;

    case WM_MOUSEMOVE:
        Mouse::_SetMousePosition(MAKEPOINTS(lParam).x, MAKEPOINTS(lParam).y);
        break;

	case WM_RBUTTONDOWN:
        Mouse::_SetMousePosition(MAKEPOINTS(lParam).x, MAKEPOINTS(lParam).y);
		Mouse::_SetMouseRightButton(true);
        break;

    case WM_RBUTTONUP:
        Mouse::_SetMousePosition(MAKEPOINTS(lParam).x, MAKEPOINTS(lParam).y);
		Mouse::_SetMouseRightButton(false);
        break;	

	case WM_DESTROY:
        g_bAppRunning = false;
        break;
    }

    return DefWindowProc(hWnd,uMessage,wParam,lParam);
}

int _OnInitInstance(HINSTANCE hInstance)
{
    WNDCLASSEX wc;

    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = _WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = NULL;
    wc.hCursor = _GetAppCursor(0);
    wc.hbrBackground = (HBRUSH) GetStockObject (BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "_GameCore_WndClass_";
    wc.hIconSm = LoadIcon (hInstance, MAKEINTRESOURCE(IDI_GAMECORE_ICON));

    if(!RegisterClassEx(&wc)) {
        return false;
	}

    g_hMainWnd = CreateWindowEx(NULL, "_GameCore_WndClass_", g_strWindowCaption,
        WS_CAPTION | WS_VISIBLE | WS_SYSMENU, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
        NULL, NULL, hInstance, NULL
	);

    if(!g_hMainWnd) {
        return false;
	}

	RECT rect;
	GetWindowRect(g_hMainWnd, &rect);
	int nFullWidth = rect.right - rect.left;
	int nFullHeight = rect.bottom - rect.top;
	
	SetWindowPos(
		g_hMainWnd, NULL,
		GetSystemMetrics(SM_CXSCREEN)/2 - nFullWidth/2,
		GetSystemMetrics(SM_CYSCREEN)/2 - nFullHeight/2,
		nFullWidth, nFullHeight, SWP_SHOWWINDOW
	);

	//SetCursor(
	//	LoadCursor(hInstance, IDC_ARROW)
	//);

	//ShowCursor(true);
		
	//ShowWindow(g_hMainWnd, SW_SHOW);

    return true;
}

