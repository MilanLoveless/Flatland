
#include "crate02.h"

extern IMAGEINFO *g_pBackBuffer;

Crate02::Crate02(int x, int y)
{
	this->rect.x = x; //1564;
	this->rect.y = y; //600;
	this->rect.w = 64;
	this->rect.h = 64;
	Load();
}

Crate02::~Crate02(void)
{
}

void Crate02::Load()
{
	g_pCrate02 = _LoadImage(0, ".\\RESOURCES\\box02.png", 64, 64);

}

void Crate02::Draw(int *video, int w, int h, int upperX, int upperY)
{
	int x = rect.x - upperX;
	int y = rect.y - upperY;

	_DrawAlphaBitmap(video, w, h, x, y, g_pCrate02->_video, 64, 64);

}