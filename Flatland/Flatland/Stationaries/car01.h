#pragma once

#include "..\\GameCore.h"
#include "Couch.h"

class Car01 : public Couch
{
public:
	Car01(int x, int y);
	~Car01(void);
	virtual void Draw(int *video, int w, int h, int upperX, int upperY);
	virtual void Load();
	IMAGEINFO *g_pCar01;
};

