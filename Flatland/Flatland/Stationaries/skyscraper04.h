#pragma once

#include "..\\GameCore.h"
#include "Couch.h"

class Skyscraper04 : public Couch
{
public:
	Skyscraper04(int x, int y);
	~Skyscraper04(void);
	virtual void Draw(int *video, int w, int h, int upperX, int upperY);
	virtual void Load();
	IMAGEINFO *g_pSkyscraper04;
};

