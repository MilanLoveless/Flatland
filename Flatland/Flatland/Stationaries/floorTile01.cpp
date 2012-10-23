
#include "floorTile01.h"

extern IMAGEINFO *g_pBackBuffer;

Floor01::Floor01(int x, int y)
{
	this->rect.x = x;
	this->rect.y = y;
	this->rect.w = 192;
	this->rect.h = 32;
	Load();
	this->Colliable = true;
}

Floor01::~Floor01(void)
{
}

void Floor01::Load()
{
	g_pFloor01 = _LoadImage(0, ".\\RESOURCES\\floorTile.png", 192, 32);
}

void Floor01::Draw(int *video, int w, int h, int upperX, int upperY)
{
	int x = rect.x - upperX;
	int y = rect.y - upperY;

	_DrawAlphaBitmap(video, w, h, x, y, g_pFloor01->_video, 192, 32);

}