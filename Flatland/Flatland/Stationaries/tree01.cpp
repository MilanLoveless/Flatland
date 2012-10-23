
#include "tree01.h"

extern IMAGEINFO *g_pBackBuffer;

Tree01::Tree01(int x, int y)
{
	this->rect.x = x;
	this->rect.y = y;
	this->rect.w = 320;
	this->rect.h = 465;
	Load();
}

Tree01::~Tree01(void)
{
}

void Tree01::Load()
{
	g_pTree01 = _LoadImage(0, ".\\RESOURCES\\tree01.png", 320, 465);

}

void Tree01::Draw(int *video, int w, int h, int upperX, int upperY)
{
	int x = rect.x - upperX;
	int y = rect.y - upperY;

	_DrawAlphaBitmap(video, w, h, x, y, g_pTree01->_video, 320, 465);

}