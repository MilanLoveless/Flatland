
#include "cloud01.h"

extern IMAGEINFO *g_pBackBuffer;

Cloud01::Cloud01(int x, int y)
{
	this->rect.x = x;
	this->rect.y = y;
	this->rect.w = 224;
	this->rect.h = 160;
	Load();
}

Cloud01::~Cloud01(void)
{
}

void Cloud01::Load()
{
	g_pCloud01 = _LoadImage(0, ".\\RESOURCES\\cloud01.png", 224, 160);

}

void Cloud01::Draw(int *video, int w, int h, int upperX, int upperY)
{
	int x = rect.x - upperX;
	int y = rect.y - upperY;

	_DrawAlphaBitmap(video, w, h, x, y, g_pCloud01->_video, 224, 160);

}