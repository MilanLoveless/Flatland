
#include "car01.h"

extern IMAGEINFO *g_pBackBuffer;

Car01::Car01(int x, int y)
{
	this->rect.x = x; //1700;
	this->rect.y = y; //538;
	this->rect.w = 258;
	this->rect.h = 128;
	Load();
}

Car01::~Car01(void)
{
}

void Car01::Load()
{
	g_pCar01 = _LoadImage(0, ".\\RESOURCES\\car.png", 258, 128);

}

void Car01::Draw(int *video, int w, int h, int upperX, int upperY)
{
	int x = rect.x - upperX;
	int y = rect.y - upperY;

	_DrawAlphaBitmap(video, w, h, x, y, g_pCar01->_video, 258, 128);

}