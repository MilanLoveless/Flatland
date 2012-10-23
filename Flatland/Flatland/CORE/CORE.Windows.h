// CORE.Windows.h
//////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __CORE_WINDOWS_H_
#define __CORE_WINDOWS_H_

extern HINSTANCE g_hInstance;
extern HWND g_hMainWnd;
extern BOOL g_bAppRunning;
extern char* g_strWindowCaption;

void _SetWindowCaption(char *str);
int _OnInitInstance(HINSTANCE hInstance);
LRESULT CALLBACK _WndProc(HWND hWindow,UINT uMessage,WPARAM wParam,LPARAM lParam);

#endif