// bird.h
//////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "mobileentity.h"
class BirdObject :
	public MobileEntity
{
public:
	BirdObject(int x, int y);
	~BirdObject(void);
	void Draw(int upperX, int upperY);
	void Update();
	float _f4Frame, _f91Frame;
	virtual Rect BoundingBox();
	virtual void Move();
private:
	IMAGEINFO *g_pBirdCells;
	AnimationSystem _BirdAnimation;
};

