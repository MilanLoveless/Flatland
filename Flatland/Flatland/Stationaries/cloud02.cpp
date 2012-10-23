
#include "cloud02.h"

extern IMAGEINFO *g_pBackBuffer;

Cloud02::Cloud02(int x, int y)
{
	this->rect.x = x;
	this->rect.y = y;
	this->rect.w = 192;
	this->rect.h = 192;
	Load();
}

Cloud02::~Cloud02(void)
{
}

void Cloud02::Load()
{
	g_pCloud02 = _LoadImage(0, ".\\RESOURCES\\cloud02.png", 192, 192);

}

void Cloud02::Draw(int *video, int w, int h, int upperX, int upperY)
{
	int x = rect.x - upperX;
	int y = rect.y - upperY;

	_DrawAlphaBitmap(video, w, h, x, y, g_pCloud02->_video, 192, 192);

}