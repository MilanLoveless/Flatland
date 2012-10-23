
#include "door01.h"

extern IMAGEINFO *g_pBackBuffer;

Door01::Door01(int x, int y)
{
	this->rect.x = x;
	this->rect.y = y;
	this->rect.w = 128;
	this->rect.h = 125;
	Load();
}

Door01::~Door01(void)
{
}

void Door01::Load()
{
	g_pDoor01 = _LoadImage(0, ".\\RESOURCES\\door01.png", 128, 125);

}

void Door01::Draw(int *video, int w, int h, int upperX, int upperY)
{
	int x = rect.x - upperX;
	int y = rect.y - upperY;

	_DrawAlphaBitmap(video, w, h, x, y, g_pDoor01->_video, 128, 125);

}