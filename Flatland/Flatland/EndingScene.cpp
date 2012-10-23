#include "EndingScene.h"


EndingScene::EndingScene(void)
{
	yOffset = 0;
	count = 0;
}


EndingScene::~EndingScene(void)
{
}

void EndingScene::Load()
{
	g_pEnding = _LoadImage(3, ".\\RESOURCES\\credits1.png", 1024, 2160);
}

void EndingScene::Draw(int *video, int w, int h)
{
	_DrawBitmapOffset(video, w, h, 128, 0,1024, WINDOW_HEIGHT, g_pEnding->_video,0, yOffset, 1024, 2160);
}
void EndingScene::Update()
{
	count++;
	if(count > 50)
	{
		yOffset++;
	}
	if(yOffset > 2160 - 720)
	{
		yOffset = 2160 - 720;
	}
	if(yOffset == 2160 - 720)
	{
		if(Mouse::m_LeftButtonDown)
		{
			Mouse::m_LeftButtonDown = false;
			ShowMenu();
		}
	}

}