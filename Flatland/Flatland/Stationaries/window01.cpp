
#include "window01.h"

extern IMAGEINFO *g_pBackBuffer;

Window01::Window01(int x, int y)
{
	this->rect.x = x;
	this->rect.y = y;
	this->rect.w = 128;
	this->rect.h = 128;
	Load();
}

Window01::~Window01(void)
{
}

void Window01::Load()
{
	g_pWindow01 = _LoadImage(0, ".\\RESOURCES\\house01_windowBack.png", 128, 128);

}

void Window01::Draw(int *video, int w, int h, int upperX, int upperY)
{
	int x = rect.x - upperX;
	int y = rect.y - upperY;

	_DrawAlphaBitmap(video, w, h, x, y, g_pWindow01->_video, 128, 128);

}