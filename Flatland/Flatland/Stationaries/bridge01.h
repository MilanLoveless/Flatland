#pragma once

#include "..\\GameCore.h"
#include "Couch.h"

class Bridge01 : public Couch
{
public:
	Bridge01(int x, int y);
	~Bridge01(void);
	virtual void Draw(int *video, int w, int h, int upperX, int upperY);
	virtual void Load();
	IMAGEINFO *g_pBridge01;
	IMAGEINFO *g_pBridge02;
	IMAGEINFO *g_pBridge03;
};

