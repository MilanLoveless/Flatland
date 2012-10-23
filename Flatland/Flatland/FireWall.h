#pragma once
#include "mobileentity.h"
class FireWall :
	public MobileEntity
{
public:
	FireWall(void);
	~FireWall(void);
	virtual void Draw(int upperX, int upperY);
	virtual void Update();
	virtual Rect BoundingBox();
private:
	IMAGEINFO *g_pFireWall;
	int count;
};

