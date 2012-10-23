
#include "bridge01.h"

extern IMAGEINFO *g_pBackBuffer;

Bridge01::Bridge01(int x, int y)
{
	this->rect.x = x;//1700;
	this->rect.y = y;
	this->rect.w = 1600;
	this->rect.h = 768;
	Load();
}

Bridge01::~Bridge01(void)
{
}

void Bridge01::Load()
{
	g_pBridge01 = _LoadImage(0, ".\\RESOURCES\\bridgeLeft.png", 518, 315);
	g_pBridge02 = _LoadImage(0, ".\\RESOURCES\\bridgeCenter.png", 543, 98);
	g_pBridge03 = _LoadImage(0, ".\\RESOURCES\\bridgeRight.png", 516, 315);

}

void Bridge01::Draw(int *video, int w, int h, int upperX, int upperY)
{
	int x = rect.x - upperX;
	int y = rect.y - upperY;

	_DrawAlphaBitmap(video, w, h, x, y, g_pBridge01->_video, 518, 315);
	x += 518;
	_DrawAlphaBitmap(video, w, h, x, y + 216, g_pBridge02->_video, 543, 98);
	_DrawAlphaBitmap(video, w, h, x + 543, y, g_pBridge03->_video, 516, 315);

}