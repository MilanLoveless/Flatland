//Rat.cpp
//////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
#include "paperBall.h"
#include "GameCore.h"

extern IMAGEINFO *g_pBackBuffer;

paperBall::paperBall(int x, int y)
{
	this->rect.x = x;
	this->rect.y = y;
	this->rect.w = 32;
	this->rect.h = 32;
	g_pBalls = _LoadImage(0, ".\\RESOURCES\\paperball_32x32.png", 32, 32);
	acceleration = 1.0f;
	birth = time(NULL);
	deathtime = birth + 1;
}

paperBall::~paperBall(void)
{
}

Rect paperBall::BoundingBox()
{
	Rect r(rect.x, rect.y, rect.w, rect.h);
	return r;
}

void paperBall::Draw(int upperX, int upperY)
{
	int x = rect.x - upperX;
	int y = rect.y - upperY;
	DrawAlphaBitmap(x, y, g_pBalls->_video, rect.w, rect.h);
}

void paperBall::Update()
{
	Move();
}