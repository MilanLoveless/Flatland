#pragma once

#include "..\\GameCore.h"

#include "Couch.h"

class Cloud02 : public Couch
{
public:
	Cloud02(int x, int y);
	~Cloud02(void);
	virtual void Draw(int *video, int w, int h, int upperX, int upperY);
	virtual void Load();
	IMAGEINFO *g_pCloud02;
};

