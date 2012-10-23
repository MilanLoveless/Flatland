#pragma once

#include "..\\GameCore.h"
#include "Couch.h"

class Crate03 : public Couch
{
public:
	Crate03(int x, int y);
	~Crate03(void);
	virtual void Draw(int *video, int w, int h, int upperX, int upperY);
	virtual void Load();
	IMAGEINFO *g_pCrate03;
};

