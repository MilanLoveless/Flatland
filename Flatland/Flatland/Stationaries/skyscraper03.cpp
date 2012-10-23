
#include "skyscraper03.h"

extern IMAGEINFO *g_pBackBuffer;

Skyscraper03::Skyscraper03(int x, int y)
{
	this->rect.x = x;
	this->rect.y = y;
	this->rect.w = 416;
	this->rect.h = 743;
	Load();
}

Skyscraper03::~Skyscraper03(void)
{
}

void Skyscraper03::Load()
{
	g_pSkyscraper03 = _LoadImage(0, ".\\RESOURCES\\level_02_Assests\\skyScaper03.png", 416, 743);

}

void Skyscraper03::Draw(int *video, int w, int h, int upperX, int upperY)
{
	int x = rect.x - upperX;
	int y = rect.y - upperY;

	_DrawAlphaBitmap(video, w, h, x, y, g_pSkyscraper03->_video, 416, 743);

}