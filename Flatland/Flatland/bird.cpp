//bird.cpp
//////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
#include "bird.h"
#include "GameCore.h"

extern IMAGEINFO *g_pBackBuffer;

BirdObject::BirdObject(int x, int y)
{
	this->rect.x = x;
	this->rect.y = y;
	this->rect.w = 158;
	this->rect.h = 128;
	_f4Frame = 0.0;
	g_pBirdCells = _LoadImage(0, ".\\RESOURCES\\MadBird_632x128.png", 632, 128);
	this->_BirdAnimation._CreateAnimation("4_FRAME", &_f4Frame, LINEAR, 0, 3.999, 0, 1, OPTION_REPEAT);
	this->_BirdAnimation._CreateAnimation("91_FRAME", &_f91Frame, LINEAR, 0, 110.999, 0, 4, OPTION_REPEAT);
	acceleration = 1.0f;
	maxVelX = 3;
	jumpVel = -15;
}

BirdObject::~BirdObject(void)
{
}

Rect BirdObject::BoundingBox()
{
	Rect r(rect.x + 5, rect.y,rect.w - 10, rect.h);
	return r;
}

void BirdObject::Move()
{
		switch(movement) {
	case RIGHT:
		velX += acceleration;
		if(velX > maxVelX)
			velX = maxVelX;
		break;
	case LEFT:
		velX -= acceleration;
		if(velX < -1 * maxVelX)
			velX = -1 * maxVelX;
		break;
	case STOP:
		if( velX > 0)
		{
			velX -= acceleration;
			if(velX < 0)
				velX = 0;
		}
		else if(velX < 0)
		{
			velX += acceleration;
			if(velX > 0)
				velX = 0;
		}
		break;
	}
	rect.x += velX;
	if(rect.x < 0)
		rect.x = 0;
	else if(rect.x + rect.w > LEVEL_LENGTH - 7)
	{
		rect.x = LEVEL_LENGTH - rect.w - 7;
	}
	
	//Handle Y movement

	velY += 0;
	if(velY > 16)
		velY = 16;
	rect.y += velY;
	if(rect.y + rect.h > LEVEL_HEIGHT - 28)
	{
		rect.y = LEVEL_HEIGHT - rect.h - 28;
		velY = 0;
		jump = false;
	}
	else if(rect.y < 0)
	{
		rect.y = 0;
		velY = 0;
		jump = false;
	}
}
void BirdObject::Draw(int upperX, int upperY)
{
	this->_BirdAnimation._RunAnimations();

	int x = rect.x - upperX;
	int y = rect.y - upperY;
	if(movement == STOP)
	{
		if(facing == LEFT)
		{
			DrawAlphaCellFlipped(x, y, g_pBirdCells->_video, 2, 0, rect.w, rect.h, 632, 128);
		}
		else
		{
			DrawAlphaCell(x, y, g_pBirdCells->_video, 2, 0, rect.w, rect.h, 632, 128);
		}
	} 
	else if (movement == RIGHT)
	{
		DrawAlphaCell(x, y, g_pBirdCells->_video, _f4Frame, 0, rect.w, rect.h, 632, 128);
	} 
	else 
	{
		DrawAlphaCellFlipped(x, y, g_pBirdCells->_video, _f4Frame, 0, rect.w, rect.h, 632, 128);
	}
}

void BirdObject::Update()
{
	if(_f91Frame < 25) StopMovement();
	else if(_f91Frame < 55) MoveRight();
	else if(_f91Frame < 80) StopMovement();
	else if(_f91Frame < 111) MoveLeft();

	Move();
}