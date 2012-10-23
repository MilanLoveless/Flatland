
#include "crate03.h"

extern IMAGEINFO *g_pBackBuffer;

Crate03::Crate03(int x, int y)
{
	this->rect.x = x; //1628;
	this->rect.y = y; //600;
	this->rect.w = 64;
	this->rect.h = 64;
	Load();
}

Crate03::~Crate03(void)
{
}

void Crate03::Load()
{
	g_pCrate03 = _LoadImage(0, ".\\RESOURCES\\box03.png", 64, 64);

}

void Crate03::Draw(int *video, int w, int h, int upperX, int upperY)
{
	int x = rect.x - upperX;
	int y = rect.y - upperY;

	_DrawAlphaBitmap(video, w, h, x, y, g_pCrate03->_video, 64, 64);

}