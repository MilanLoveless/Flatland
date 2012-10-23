#include "GameCore.h"


// GameCore.cpp
////////////////////////////////////////////////////////////////////////////////////////////

#include "GameCore.h"
#include "Scene.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "GameOverScene.h"
#include "EndingScene.h"

extern bool fire;

TEXTUREINFO *g_pBackBuffer;

int _upperX = 0;
int _upperY = 0;

int redTapes;

//AnimationSystem _AnimationSystem;

////////////////////////////////////////////////////////////////////////////////////////////

const int TICKS_PER_SECOND = 50;
const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
const int MAX_FRAMESKIP = 10;

AnimationSystem _AnimationSystem;

////////////////////////////////////////////////////////////////////////////////////////////

Scene* currentScene;
MenuScene Menu;

////////////////////////////////////////////////////////////////////////////////////////////

void _OnInitialize() {
	
	_SetWindowCaption("GameCore");
	
	_LoadSoundBank(0);

	// Create display surfaces
	g_pBackBuffer = _CreateTexture(0, WINDOW_WIDTH, WINDOW_HEIGHT);

	// Load image resources
	// Example: g_pImageCompany = _LoadImage(0, ".\\RESOURCES\\COMPANYSCREEN_728x532.png", 728, 532);

	currentScene = new MenuScene();
	currentScene->Load();

	ShowMenu();

}

void ShowMenu()
{
	delete(currentScene);
	redTapes = 5;
	fire = false;
	currentScene = new MenuScene();
	currentScene->Load();
}

void ShowGame(int level)
{
	delete(currentScene);
	currentScene = new GameScene(level);
	currentScene->Load();
}

void ShowEnding()
{
	delete(currentScene);
	currentScene = new EndingScene();
	currentScene->Load();
}

void ShowGameOver()
{
	delete(currentScene);
	currentScene = new GameOverScene();
	currentScene->Load();
}

void _OnUninitialize() {
	// Unload display surfaces
	_UnloadImage(&g_pBackBuffer);

	// Unload images (Example...)
	// Example: _UnloadImage(&g_pImageCompany);
	delete(currentScene);
}


void _OnFrame() {
	long int start = GetTickCount();
	currentScene->Update();
	//_AnimationSystem._UpdateCurrentTime();
	//_AnimationSystem._RunAnimations();
	////////////////////////////////////////////////////////////////////////////////////////////////////
	while((start + SKIP_TICKS) > GetTickCount())
	{
		_ClearBackBuffer();
		_BeginDrawing();

		_LockTexture(g_pBackBuffer);
		_ClearScreen(g_pBackBuffer, 0xFFFFFFFF);

		_AnimationSystem._UpdateCurrentTime();
		_AnimationSystem._RunAnimations();

		int *video = g_pBackBuffer->_video;
		int w = g_pBackBuffer->_nWidth;
		int h = g_pBackBuffer->_nHeight;

		currentScene->Draw(video, w, h);

		_UnlockTexture(g_pBackBuffer);

		_FlipSurface(g_pBackBuffer->_pSurface);

		_EndDrawing();
		_DisplayBackBuffer();
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////

}
