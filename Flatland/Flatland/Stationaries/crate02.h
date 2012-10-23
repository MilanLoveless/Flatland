#pragma once

#include "..\\GameCore.h"
#include "Couch.h"

class Crate02 : public Couch
{
public:
	Crate02(int x, int y);
	~Crate02(void);
	virtual void Draw(int *video, int w, int h, int upperX, int upperY);
	virtual void Load();
	IMAGEINFO *g_pCrate02;
};

