// CORE.Keyboard.h
///////////////////////////////////////////////////////////////////////////////

#pragma once
//#ifdef __CORE_KEYBOARD_H_
//#define __CORE_KEYBOARD_H_

class Keyboard {
public:
	static bool k_TAB;
	static bool k_RETURN;
	static bool k_SHIFT;
	static bool k_CONTROL;
	static bool k_ESCAPE;
	static bool k_SPACE;
	static bool k_END;
	static bool k_HOME;
	static bool k_LEFT;
	static bool k_UP;
	static bool k_RIGHT;
	static bool k_DOWN;
	static bool k_INSERT;
	static bool k_DELETE;
	static bool k_NUMPAD0;
	static bool k_NUMPAD1;
	static bool k_NUMPAD2;
	static bool k_NUMPAD3;
	static bool k_NUMPAD4;
	static bool k_NUMPAD5;
	static bool k_NUMPAD6;
	static bool k_NUMPAD7;
	static bool k_NUMPAD8;
	static bool k_NUMPAD9;
	static bool k_MULTIPLY;
	static bool k_ADD;
	static bool k_SEPARATOR;
	static bool k_SUBTRACT;
	static bool k_DECIMAL;
	static bool k_DIVIDE;
	static bool k_F1;
	static bool k_F2;
	static bool k_F3;
	static bool k_F4;
	static bool k_F5;
	static bool k_F6;
	static bool k_F7;
	static bool k_F8;
	static bool k_F9;
	static bool k_F10;
	static bool k_F11;
	static bool k_F12;
	static bool k_NUMLOCK;
	static bool k_SCROLL;
	static bool k_LEFT_SHIFT;
	static bool k_RIGHT_SHIFT;
	static bool k_LEFT_CONTROL;
	static bool k_RIGHT_CONTROL;

	static bool k_0;
	static bool k_1;
	static bool k_2;
	static bool k_3;
	static bool k_4;
	static bool k_5;
	static bool k_6;
	static bool k_7;
	static bool k_8;
	static bool k_9;
	static bool k_A;
	static bool k_B;
	static bool k_C;
	static bool k_D;
	static bool k_E;
	static bool k_F;
	static bool k_G;
	static bool k_H;
	static bool k_I;
	static bool k_J;
	static bool k_K;
	static bool k_L;
	static bool k_M;
	static bool k_N;
	static bool k_O;
	static bool k_P;
	static bool k_Q;
	static bool k_R;
	static bool k_S;
	static bool k_T;
	static bool k_U;
	static bool k_V;
	static bool k_W;
	static bool k_X;
	static bool k_Y;
	static bool k_Z;

	static void _Initialize();
	static void _SetKeyboardKey(UINT vkey, bool bValue);

};

#define VK_0 0x30
#define VK_1 0x31
#define VK_2 0x32
#define VK_3 0x33
#define VK_4 0x34
#define VK_5 0x35
#define VK_6 0x36
#define VK_7 0x37
#define VK_8 0x38
#define VK_9 0x39

#define VK_A 0x41
#define VK_B 0x42
#define VK_C 0x43
#define VK_D 0x44
#define VK_E 0x45
#define VK_F 0x46
#define VK_G 0x47
#define VK_H 0x48
#define VK_I 0x49
#define VK_J 0x4A
#define VK_K 0x4B
#define VK_L 0x4C
#define VK_M 0x4D
#define VK_N 0x4E
#define VK_O 0x4F
#define VK_P 0x50
#define VK_Q 0x51
#define VK_R 0x52
#define VK_S 0x53
#define VK_T 0x54
#define VK_U 0x55
#define VK_V 0x56
#define VK_W 0x57
#define VK_X 0x58
#define VK_Y 0x59
#define VK_Z 0x5A

//#endif