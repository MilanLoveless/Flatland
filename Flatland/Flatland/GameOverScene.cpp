#include "GameOverScene.h"


GameOverScene::GameOverScene(void)
{
}


GameOverScene::~GameOverScene(void)
{
}

void GameOverScene::Draw(int *video, int w, int h)
{
	_DrawBitmap(video,w,h,128,0,g_pDeath->_video,1024,720);
}

void GameOverScene::Update()
{
	if(Mouse::m_LeftButtonDown)
	{
		Mouse::m_LeftButtonDown = false;
		ShowMenu();
	}
}

void GameOverScene::Load()
{
	g_pDeath = _LoadImage(3, ".\\RESOURCES\\gameOver.png", 1024, 720);
}