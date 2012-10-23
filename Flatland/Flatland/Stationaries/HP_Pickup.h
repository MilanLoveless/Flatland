#pragma once

#include "..\\GameCore.h"
#include "Couch.h"

class HP_Pickup : public Couch
{
public:
	HP_Pickup(int x, int y);
	~HP_Pickup(void);
	virtual void Draw(int *video, int w, int h, int upperX, int upperY);
	virtual void Load();
	IMAGEINFO *g_pHP_Pickup;
};

