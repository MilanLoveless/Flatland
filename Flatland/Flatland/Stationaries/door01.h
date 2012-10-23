#pragma once

#include "..\\GameCore.h"
#include "Couch.h"

class Door01 : public Couch
{
public:
	Door01(int x, int y);
	~Door01(void);
	virtual void Draw(int *video, int w, int h, int upperX, int upperY);
	virtual void Load();
	IMAGEINFO *g_pDoor01;
};

