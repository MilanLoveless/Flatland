#pragma once

#include "..\\GameCore.h"
#include "Couch.h"

class Van01 : public Couch
{
public:
	Van01(int x, int y);
	~Van01(void);
	virtual void Draw(int *video, int w, int h, int upperX, int upperY);
	virtual void Load();
	IMAGEINFO *g_pVan01;
};

