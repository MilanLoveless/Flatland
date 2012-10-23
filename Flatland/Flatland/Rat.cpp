//Rat.cpp
//////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
#include "Rat.h"
#include "GameCore.h"

extern IMAGEINFO *g_pBackBuffer;

RatObject::RatObject(int x, int y)
{
	this->rect.x = x;
	this->rect.y = y;
	this->rect.w = 128;
	this->rect.h = 64;
	_f4Frame = 0.0;
	g_pRatCells = _LoadImage(0, ".\\RESOURCES\\charSpriteSheet02-2.png", 1280, 128);
	this->_RatAnimation._CreateAnimation("4_FRAME", &_f4Frame, LINEAR, 0, 3.999, 0, 1, OPTION_REPEAT);
	this->_RatAnimation._CreateAnimation("91_FRAME", &_f91Frame, LINEAR, 0, 110.999, 0, 4, OPTION_REPEAT);
	acceleration = 1.0f;
	maxVelX = 3;
	jumpVel = -15;
}

RatObject::~RatObject(void)
{
}

Rect RatObject::BoundingBox()
{
	Rect r(rect.x + 5, rect.y,rect.w - 10, rect.h);
	return r;
}

void RatObject::Draw(int upperX, int upperY)
{
	this->_RatAnimation._RunAnimations();

	int x = rect.x - upperX;
	int y = rect.y - upperY;
	if(movement == STOP)
	{
		if(facing == LEFT)
		{
			DrawAlphaCell(x, y, g_pRatCells->_video, 2, 0, rect.w, rect.h, 1280, 128);
		}
		else
		{
			DrawAlphaCellFlipped(x, y, g_pRatCells->_video, 2, 0, rect.w, rect.h, 1280, 128);
		}
	} 
	else if (movement == RIGHT)
	{
		DrawAlphaCellFlipped(x, y, g_pRatCells->_video, _f4Frame, 0, rect.w, rect.h, 1280, 128);
	} 
	else 
	{
		DrawAlphaCell(x, y, g_pRatCells->_video, _f4Frame, 0, rect.w, rect.h, 1280, 128);
	}
}

void RatObject::Update()
{
	if(_f91Frame < 25) StopMovement();
	else if(_f91Frame < 55) MoveRight();
	else if(_f91Frame < 80) StopMovement();
	else if(_f91Frame < 111) MoveLeft();

	Move();
}