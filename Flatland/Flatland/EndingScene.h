#pragma once
#include "scene.h"
#include "GameCore.h"
class EndingScene :
	public Scene
{
public:
	EndingScene(void);
	~EndingScene(void);
	virtual void Load();
	virtual void Draw(int *video, int w, int h);
	virtual void Update();
private:
	IMAGEINFO *g_pEnding;
	int count;
	int yOffset;
};

