#pragma once
#include "mobileentity.h"

extern int redTapes;

class Player :
	public MobileEntity
{
public:
	Player(void);
	~Player(void);
	virtual void Draw(int upperX, int upperY);
	virtual void Update();
	bool isShooting;
	float _fTenFrame;
	float _f5Frame;
	void OneUp();
	void OneDown();
	void Kill();
	bool isDead(){ return (redTapes < 1); };
	bool isInvincible() { return (invinCount > 0); };
	int getLife() { return redTapes; };
	virtual Rect BoundingBox();
	void setX(int x) { rect.x = x; };
	void setY(int y) { rect.y = y; };
private:
	IMAGEINFO *g_pCharacterCells2;
	AnimationSystem _PlayerAnimation;
	//int redTapes;
	int invinCount;
};

