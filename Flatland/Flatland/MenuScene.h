#pragma once
#include "scene.h"
#include "GameCore.h"

class MenuScene :
	public Scene
{
public:
	MenuScene(void);
	~MenuScene(void);
	
	virtual void Draw(int *video, int w, int h);
	virtual void Update();
	virtual void Load();
	
};

