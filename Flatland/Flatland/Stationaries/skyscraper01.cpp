
#include "skyscraper01.h"

extern IMAGEINFO *g_pBackBuffer;

Skyscraper01::Skyscraper01(int x, int y)
{
	this->rect.x = x;
	this->rect.y = y;
	this->rect.w = 384;
	this->rect.h = 768;
	Load();
}

Skyscraper01::~Skyscraper01(void)
{
}

void Skyscraper01::Load()
{
	g_pSkyscraper01 = _LoadImage(0, ".\\RESOURCES\\level_02_Assests\\skyScaper01.png", 384, 768);

}

void Skyscraper01::Draw(int *video, int w, int h, int upperX, int upperY)
{
	int x = rect.x - upperX;
	int y = rect.y - upperY;

	_DrawAlphaBitmap(video, w, h, x, y, g_pSkyscraper01->_video, 384, 768);

}