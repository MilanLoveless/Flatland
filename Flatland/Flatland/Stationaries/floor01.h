#pragma once

#include "..\\GameCore.h"
#include "Couch.h"

class Floor02 : Couch
{
public:
	Floor02(void);
	~Floor02(void);
	virtual void Draw(int *video, int w, int h, int upperX, int upperY);
	virtual void Load();
	IMAGEINFO *g_pFloor02;
};

