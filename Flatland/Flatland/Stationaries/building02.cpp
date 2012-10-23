
#include "building02.h"

extern IMAGEINFO *g_pBackBuffer;

Building02::Building02(int x, int y)
{
	this->rect.x = x;
	this->rect.y = y;
	this->rect.w = 384;
	this->rect.h = 256;
	Load();
}

Building02::~Building02(void)
{
}

void Building02::Load()
{
	g_pBuilding02 = _LoadImage(0, ".\\RESOURCES\\house02.png", 384, 256);

}

void Building02::Draw(int *video, int w, int h, int upperX, int upperY)
{
	int x = rect.x - upperX;
	int y = rect.y - upperY;

	_DrawAlphaBitmap(video, w, h, x, y, g_pBuilding02->_video, 384, 256);

}