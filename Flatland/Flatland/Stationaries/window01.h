#pragma once

#include "..\\GameCore.h"
#include "Couch.h"

class Window01 : public Couch
{
public:
	Window01(int x, int y);
	~Window01(void);
	virtual void Draw(int *video, int w, int h, int upperX, int upperY);
	virtual void Load();
	IMAGEINFO *g_pWindow01;
};

