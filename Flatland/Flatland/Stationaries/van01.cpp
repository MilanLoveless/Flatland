
#include "van01.h"

extern IMAGEINFO *g_pBackBuffer;

Van01::Van01(int x, int y)
{
	this->rect.x = x; //2400;
	this->rect.y = y; //538;
	this->rect.w = 320;
	this->rect.h = 128;
	Load();
}

Van01::~Van01(void)
{
}

void Van01::Load()
{
	g_pVan01 = _LoadImage(0, ".\\RESOURCES\\van.png", 320, 128);

}

void Van01::Draw(int *video, int w, int h, int upperX, int upperY)
{
	int x = rect.x - upperX;
	int y = rect.y - upperY;

	_DrawAlphaBitmap(video, w, h, x, y, g_pVan01->_video, 320, 128);

}