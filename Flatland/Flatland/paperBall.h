// paperBall.h
//////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Projectile.h"

class paperBall :
	public Projectile
{
public:
	paperBall(int x, int y);
	~paperBall(void);
	void Draw(int upperX, int upperY);
	void Update();
	virtual Rect BoundingBox();
private:
	IMAGEINFO *g_pBalls;
};

