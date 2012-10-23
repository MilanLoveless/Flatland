#include "FireWall.h"
#include "GameCore.h"


FireWall::FireWall(void)
{
	g_pFireWall = _LoadImage(0, ".\\RESOURCES\\fireSprite.png", 2560, 1440);
	rect.x = LEVEL_LENGTH;
	rect.y = 0;
	rect.w = 640;
	rect.h = 1440;
	acceleration = 0.1f;
	maxVelX = 10;
	MoveLeft();
	count = 0;
}


FireWall::~FireWall(void)
{
}

Rect FireWall::BoundingBox()
{
	Rect r(rect.x + 160, rect.y,rect.w - 160, rect.h);
	return r;
}

void FireWall::Update()
{
	Move();
	count++;
}

void FireWall::Draw(int upperX, int upperY)
{
	int x = rect.x - upperX;
	int y = rect.y - upperY;
	int frame = count / 2;
	frame = frame % 4;
	DrawAlphaCell(x, y, g_pFireWall->_video, frame, 0, rect.w, rect.h, 2560, 1440);
}