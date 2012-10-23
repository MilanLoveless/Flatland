#pragma once

#include "..\\GameCore.h"
#include "Couch.h"

class Cloud01 : public Couch
{
public:
	Cloud01(int x, int y);
	~Cloud01(void);
	virtual void Draw(int *video, int w, int h, int upperX, int upperY);
	virtual void Load();
	IMAGEINFO *g_pCloud01;
};

