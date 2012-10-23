
#include "skyscraper02.h"

extern IMAGEINFO *g_pBackBuffer;

Skyscraper02::Skyscraper02(int x, int y)
{
	this->rect.x = x; //300;
	this->rect.y = y; //0;
	this->rect.w = 640;
	this->rect.h = 640;
	Load();
}

Skyscraper02::~Skyscraper02(void)
{
}

void Skyscraper02::Load()
{
	g_pSkyscraper02 = _LoadImage(0, ".\\RESOURCES\\level_02_Assests\\skyScaper02.png", 640, 640);

}

void Skyscraper02::Draw(int *video, int w, int h, int upperX, int upperY)
{
	int x = rect.x - upperX;
	int y = rect.y - upperY;

	_DrawAlphaBitmap(video, w, h, x, y, g_pSkyscraper02->_video, 640, 640);

}