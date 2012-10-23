#pragma once

#include "..\\GameCore.h"
#include "Couch.h"

class Skyscraper02 : public Couch
{
public:
	Skyscraper02(int x, int y);
	~Skyscraper02(void);
	virtual void Draw(int *video, int w, int h, int upperX, int upperY);
	virtual void Load();
	IMAGEINFO *g_pSkyscraper02;
};

