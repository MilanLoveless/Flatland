#pragma once

#include "GameCore.h"
#include <list>

enum Direction { LEFT, RIGHT, STOP };

class MobileEntity
{
public:
	MobileEntity(void);
	~MobileEntity(void);
	virtual void Move();
	void MoveRight();
	void MoveLeft();
	void Jump();
	void StopMovement();
	int getX();
	int getY();
	int getWidth();
	int getHeight();
	virtual Rect BoundingBox();
	virtual void Draw(int upperX, int upperY);
	virtual void Update();
	void invertVelX();
	void handleGeo(list<auto_ptr<Rect>> &geo);
protected :
	Direction movement;
	Direction facing;
	float acceleration;
	float jumpVel;
	float velX, velY;
	float maxVelX, maxVelY;
	float upperOffX, upperOffY;
	bool jump;
	Rect rect;
};

