#pragma once
#include "scene.h"
#include "GameCore.h"
class GameOverScene :
	public Scene
{
public:
	GameOverScene(void);
	~GameOverScene(void);
	virtual void Draw(int *video, int w, int h);
	virtual void Update();
	virtual void Load();
private:
	IMAGEINFO *g_pDeath;
};

