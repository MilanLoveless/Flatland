#pragma once

#include "..\\GameCore.h"
#include "Couch.h"

class Building01 : public Couch
{
public:
	Building01(int x, int y);
	~Building01(void);
	virtual void Draw(int *video, int w, int h, int upperX, int upperY);
	virtual void Load();
	IMAGEINFO *g_pBuild01;
};

