#pragma once

#include "..\\GameCore.h"

class Couch
{
public:
	Couch(void);
	~Couch(void);
	virtual void Draw(int *video, int w, int h, int upperX, int upperY) = 0;
	virtual void Load() = 0;
	Rect BoundingBox() { return rect; };
	Rect rect;
	bool Colliable;
};

