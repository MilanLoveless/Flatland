
#include "skyscraper04.h"

extern IMAGEINFO *g_pBackBuffer;

Skyscraper04::Skyscraper04(int x, int y)
{
	this->rect.x = x;
	this->rect.y = y;
	this->rect.w = 416;
	this->rect.h = 416;
	Load();
}

Skyscraper04::~Skyscraper04(void)
{
}

void Skyscraper04::Load()
{
	g_pSkyscraper04 = _LoadImage(0, ".\\RESOURCES\\level_02_Assests\\skyScaper04.png", 416, 416);

}

void Skyscraper04::Draw(int *video, int w, int h, int upperX, int upperY)
{
	int x = rect.x - upperX;
	int y = rect.y - upperY;

	_DrawAlphaBitmap(video, w, h, x, y, g_pSkyscraper04->_video, 416, 416);

}