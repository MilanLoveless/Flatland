
#include "table01.h"

extern IMAGEINFO *g_pBackBuffer;

Table01::Table01(int x, int y)
{
	this->rect.x = x;
	this->rect.y = y;
	this->rect.w = 128;
	this->rect.h = 80;
	Load();
}

Table01::~Table01(void)
{
}

void Table01::Load()
{
	g_pTable01 = _LoadImage(0, ".\\RESOURCES\\table01.png", 128, 80);

}

void Table01::Draw(int *video, int w, int h, int upperX, int upperY)
{
	int x = rect.x - upperX;
	int y = rect.y - upperY;

	_DrawAlphaBitmap(video, w, h, x, y, g_pTable01->_video, 128, 80);

}