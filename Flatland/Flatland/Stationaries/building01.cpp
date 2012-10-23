
//EnemyObject.cpp
//////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

#include "building01.h"

extern IMAGEINFO *g_pBackBuffer;

Building01::Building01(int x, int y)
{
	this->rect.x = x;
	this->rect.y = y;
	this->rect.w = 256;
	this->rect.h = 446;
	Load();
}

Building01::~Building01(void)
{
}

void Building01::Load()
{
	g_pBuild01 = _LoadImage(0, ".\\RESOURCES\\firstHouse.png", 256, 446);

}

void Building01::Draw(int *video, int w, int h, int upperX, int upperY)
{
	int x = rect.x - upperX;
	int y = rect.y - upperY;

	_DrawAlphaBitmap(video, w, h, x, y, g_pBuild01->_video, 256, 446);

}