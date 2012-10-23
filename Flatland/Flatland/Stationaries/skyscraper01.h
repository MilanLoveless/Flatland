#pragma once

#include "..\\GameCore.h"
#include "Couch.h"

class Skyscraper01 : public Couch
{
public:
	Skyscraper01(int x, int y);
	~Skyscraper01(void);
	virtual void Draw(int *video, int w, int h, int upperX, int upperY);
	virtual void Load();
	IMAGEINFO *g_pSkyscraper01;
};

