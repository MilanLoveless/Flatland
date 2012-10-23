
#include "floor01.h"

extern IMAGEINFO *g_pBackBuffer;

Floor02::Floor02(void)
{
	this->rect.x = 0;
	this->rect.y = 665;
	this->rect.w = 768;
	this->rect.h = 384;
	Load();
}

Floor02::~Floor02(void)
{
}

void Floor02::Load()
{
	g_pFloor02 = _LoadImage(0, ".\\RESOURCES\\floor.png", 768, 384);

}

void Floor02::Draw(int *video, int w, int h, int upperX, int upperY)
{
	int x = rect.x - upperX;
	int y = rect.y - upperY;

	_DrawAlphaBitmap(video, w, h, x, y, g_pFloor02->_video, 768, 384);

}