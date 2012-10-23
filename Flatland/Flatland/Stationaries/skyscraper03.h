#pragma once

#include "..\\GameCore.h"
#include "Couch.h"

class Skyscraper03 : public Couch
{
public:
	Skyscraper03(int x, int y);
	~Skyscraper03(void);
	virtual void Draw(int *video, int w, int h, int upperX, int upperY);
	virtual void Load();
	IMAGEINFO *g_pSkyscraper03;
};

