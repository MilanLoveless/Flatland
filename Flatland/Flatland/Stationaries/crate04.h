#pragma once

#include "..\\GameCore.h"
#include "Couch.h"

class Crate04 : public Couch
{
public:
	Crate04(int x, int y);
	~Crate04(void);
	virtual void Draw(int *video, int w, int h, int upperX, int upperY);
	virtual void Load();
	IMAGEINFO *g_pCrate04;
};

