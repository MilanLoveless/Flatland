#pragma once

#include "..\\GameCore.h"
#include "Couch.h"

class Table01 : public Couch
{
public:
	Table01(int x, int y);
	~Table01(void);
	virtual void Draw(int *video, int w, int h, int upperX, int upperY);
	virtual void Load();
	IMAGEINFO *g_pTable01;
};

