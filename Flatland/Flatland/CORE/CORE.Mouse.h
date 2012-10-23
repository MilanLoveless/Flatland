// CORE.Mouse.h
/////////////////////////////////////////////////////////////////////////////////////////

#pragma once
// NOTE: Visual Studio bug with Intellisense support
//#ifndef __CORE_MOUSE_H_
//#define __CORE_MOUSE_H_

class Mouse {
public:
	static int m_X;
	static int m_Y;

	static bool m_LeftButtonDown;
	static bool m_RightButtonDown;

	static bool _IsMouseInRect(int x1, int y1, int x2, int y2) {
		if(Mouse::m_X <= x1) return false;
		if(Mouse::m_X >= x2) return false;
		if(Mouse::m_Y <= y1) return false;
		if(Mouse::m_Y >= y2) return false;
		return true;
	}

	static void _SetMousePosition(int x, int y) {
		m_X = x;
		m_Y = y;
	}

	static void _SetMouseLeftButton(bool b) {
		m_LeftButtonDown = b;
	}


	static void _SetMouseRightButton(bool b) {
		m_RightButtonDown = b;
	}
};
//#endif