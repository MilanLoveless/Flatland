
#include "crate04.h"

extern IMAGEINFO *g_pBackBuffer;

Crate04::Crate04(int x, int y)
{
	this->rect.x = x; //1564;
	this->rect.y = y; //534;
	this->rect.w = 64;
	this->rect.h = 64;
	Load();
}

Crate04::~Crate04(void)
{
}

void Crate04::Load()
{
	g_pCrate04 = _LoadImage(0, ".\\RESOURCES\\box04.png", 64, 64);
}

void Crate04::Draw(int *video, int w, int h, int upperX, int upperY)
{
	int x = rect.x - upperX;
	int y = rect.y - upperY;

	_DrawAlphaBitmap(video, w, h, x, y, g_pCrate04->_video, 64, 64);
}