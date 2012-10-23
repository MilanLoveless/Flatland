// EnemyObject.h
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "mobileentity.h"
class EnemyObject :
	public MobileEntity
{
public:
	EnemyObject(int x, int y);
	~EnemyObject(void);
	virtual void Draw(int upperX, int upperY);
	virtual void Update();
	float _f6Frame, _f90Frame;
private:
	IMAGEINFO *g_pDogCells;
	AnimationSystem _EnemyAnimation;
};

