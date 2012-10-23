
#include "crate01.h"

extern IMAGEINFO *g_pBackBuffer;

Crate01::Crate01(int x, int y)
{
	this->rect.x = x; //1500;
	this->rect.y = y; //600;
	this->rect.w = 64;
	this->rect.h = 64;
	Load();
}

Crate01::~Crate01(void)
{
}

void Crate01::Load()
{
	g_pCrate01 = _LoadImage(0, ".\\RESOURCES\\box01.png", 64, 64);

}

void Crate01::Draw(int *video, int w, int h, int upperX, int upperY)
{
	int x = rect.x - upperX;
	int y = rect.y - upperY;

	_DrawAlphaBitmap(video, w, h, x, y, g_pCrate01->_video, 64, 64);

}