#pragma once

#include "GameCore.h"
#include <list>
#include <time.h>

class Projectile
{
public:
	Projectile(void);
	~Projectile(void);
	virtual void Move();
	int getX();
	int getY();
	int getWidth();
	int getHeight();
	virtual Rect BoundingBox();
	virtual void Draw(int upperX, int upperY);
	virtual void Update();
	void handleGeo(list<auto_ptr<Rect>> &geo);
	time_t birth;
	int deathtime;
protected :
	float acceleration;
	float velX, velY;
	float maxVelX, maxVelY;
	float upperOffX, upperOffY;
	Rect rect;
};

