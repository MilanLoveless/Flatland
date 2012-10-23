//EnemyObject.cpp
//////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
#include "EnemyObject.h"
#include "GameCore.h"

extern IMAGEINFO *g_pBackBuffer;

EnemyObject::EnemyObject(int x, int y)
{
	this->rect.x = x;
	this->rect.y = y;
	this->rect.w = 152;
	this->rect.h = 100;
	_f6Frame = 0.0;
	g_pDogCells = _LoadImage(0, ".\\RESOURCES\\angrydogSheet.png", 942, 100);
	this->_EnemyAnimation._CreateAnimation("6_FRAME", &_f6Frame, LINEAR, 0, 3.999, 0, 1, OPTION_REPEAT);
	this->_EnemyAnimation._CreateAnimation("90_FRAME", &_f90Frame, LINEAR, 0, 175.999, 0, 10, OPTION_REPEAT);
	acceleration = 1.0f;
	maxVelX = 4;
	jumpVel = -15;
}

EnemyObject::~EnemyObject(void)
{
}

void EnemyObject::Draw(int upperX, int upperY)
{
	this->_EnemyAnimation._RunAnimations();

	int x = rect.x - upperX;
	int y = rect.y - upperY;
	if(movement == STOP)
	{
		if(facing == LEFT)
		{
			DrawAlphaCell(x, y, g_pDogCells->_video, 5, 0, rect.w, rect.h, 942, 100);
		}
		else
		{
			DrawAlphaCellFlipped(x, y, g_pDogCells->_video, 5, 0, rect.w, rect.h, 942, 100);
		}
	} 
	else if (movement == RIGHT)
	{
		DrawAlphaCellFlipped(x, y, g_pDogCells->_video, 1 + _f6Frame, 0, rect.w, rect.h, 942, 100);
	} 
	else 
	{
		DrawAlphaCell(x, y, g_pDogCells->_video, 1 + _f6Frame, 0, rect.w, rect.h, 942, 100);
	}
}

void EnemyObject::Update()
{
	if(_f90Frame < 28) StopMovement();
	else if(_f90Frame < 88) MoveRight();
	else if(_f90Frame < 116) StopMovement();
	else if(_f90Frame < 176) MoveLeft();

	Move();
}