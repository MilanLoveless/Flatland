
#include "HP_Pickup.h"

extern IMAGEINFO *g_pBackBuffer;

HP_Pickup::HP_Pickup(int x, int y)
{
	this->Colliable = true;
	this->rect.x = x;
	this->rect.y = y;
	this->rect.w = 64;
	this->rect.h = 64;
	Load();
}

HP_Pickup::~HP_Pickup(void)
{
}

void HP_Pickup::Load()
{
	g_pHP_Pickup = _LoadImage(0, ".\\RESOURCES\\Health2.png", 64, 64);

}

void HP_Pickup::Draw(int *video, int w, int h, int upperX, int upperY)
{
	int x = rect.x - upperX;
	int y = rect.y - upperY;

	_DrawAlphaBitmap(video, w, h, x, y, g_pHP_Pickup->_video, 64, 64);
}