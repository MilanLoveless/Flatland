#pragma once

#include "..\\GameCore.h"
#include "Couch.h"

class Floor01 : public Couch
{
public:
	Floor01(int x, int y);
	~Floor01(void);
	virtual void Draw(int *video, int w, int h, int upperX, int upperY);
	virtual void Load();
	IMAGEINFO *g_pFloor01;
};
