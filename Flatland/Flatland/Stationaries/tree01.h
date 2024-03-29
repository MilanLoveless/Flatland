#pragma once

#include "..\\GameCore.h"
#include "Couch.h"

class Tree01 : public Couch
{
public:
	Tree01(int x, int y);
	~Tree01(void);
	virtual void Draw(int *video, int w, int h, int upperX, int upperY);
	virtual void Load();
	IMAGEINFO *g_pTree01;
};

