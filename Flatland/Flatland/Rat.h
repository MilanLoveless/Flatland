// Rat.h
//////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "mobileentity.h"
class RatObject :
	public MobileEntity
{
public:
	RatObject(int x, int y);
	~RatObject(void);
	void Draw(int upperX, int upperY);
	void Update();
	float _f4Frame, _f91Frame;
	virtual Rect BoundingBox();
private:
	IMAGEINFO *g_pRatCells;
	AnimationSystem _RatAnimation;
};

