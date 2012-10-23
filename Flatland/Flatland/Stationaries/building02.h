#pragma once

#include "..\\GameCore.h"
#include "Couch.h"

class Building02 : public Couch
{
public:
	Building02(int x, int y);
	~Building02(void);
	virtual void Draw(int *video, int w, int h, int upperX, int upperY);
	virtual void Load();
	IMAGEINFO *g_pBuilding02;
};

