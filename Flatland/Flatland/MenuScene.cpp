#include "MenuScene.h"
#include "GameCore.h"

extern IMAGEINFO *g_pBackBuffer;
IMAGEINFO *g_pTitle;
IMAGEINFO *g_pImageCompany = NULL;
IMAGEINFO *g_pImageNewGame_Idle = NULL;
IMAGEINFO *g_pImageOptions_Idle = NULL;
IMAGEINFO *g_pImageQuit_Idle = NULL;
IMAGEINFO *g_pImageNewGame_Hover = NULL;
IMAGEINFO *g_pImageOptions_Hover = NULL;
IMAGEINFO *g_pImageQuit_Hover = NULL;
IMAGEINFO *g_pImageBalerUp = NULL;
IMAGEINFO *g_pImageBalerDown = NULL;

int CURRENT_SCREEN;

const int MENU_STATE_TITLE = 0;
const int MENU_STATE_BALER_DOWN = 10;
const int MENU_STATE_BALER_UP = 11;
const int MENU_STATE_OPTIONS = 20;


AnimationSystem _BalerAnimation;
float _f20Frame = 0;
int count = 0;


MenuScene::MenuScene(void)
{	
	CURRENT_SCREEN = MENU_STATE_TITLE;
	g_pTitle = _LoadImage(3, ".\\RESOURCES\\title_img_574x432.png", 574, 432);
}


MenuScene::~MenuScene(void)
{
	_UnloadImage(&g_pImageCompany);
	_UnloadImage(&g_pImageNewGame_Idle);
	_UnloadImage(&g_pTitle);
}


void MenuScene::Draw(int *video, int w, int h)
{
	if(CURRENT_SCREEN == MENU_STATE_TITLE) {
		_DrawBitmap(video, w, h, WINDOW_WIDTH/2 - 574/2, -200, g_pImageBalerDown->_video,574, 365);
		_DrawBitmap(video, w, h, WINDOW_WIDTH/2 - 574/2, 520, g_pImageBalerUp->_video,574, 365);
		_DrawBitmap(video, w, h, WINDOW_WIDTH/2 - 574/2, WINDOW_HEIGHT/2 - 432/2, g_pImageCompany->_video,574, 432);
		if(Mouse::m_LeftButtonDown) {
			CURRENT_SCREEN = MENU_STATE_BALER_DOWN;
			Mouse::m_LeftButtonDown = false;
		}
	}

	else if(CURRENT_SCREEN == MENU_STATE_BALER_DOWN) {
		
		_DrawBitmap(video, w, h, WINDOW_WIDTH/2 - 574/2, WINDOW_HEIGHT/2 - 432/2, g_pImageCompany->_video,574, 432);
		_DrawBitmap(video, w, h, WINDOW_WIDTH/2 - 574/2, -200 + 6 * count, g_pImageBalerDown->_video, 574, 365);
		_DrawBitmap(video, w, h, WINDOW_WIDTH/2 - 574/2, 520 - 6 * count, g_pImageBalerUp->_video, 574, 365);
		count++;
		if(count > 30)	{
			_PlaySoundEffect(0, 0);
			CURRENT_SCREEN = MENU_STATE_BALER_UP;
			count = 0;
		}

	}

	else if(CURRENT_SCREEN == MENU_STATE_BALER_UP) {
		
		_DrawBitmap(video, w, h, 410, 150, g_pImageNewGame_Idle->_video,466, 113);
		_DrawBitmap(video, w, h, 410, 300, g_pImageOptions_Idle->_video,466, 113);
		_DrawBitmap(video, w, h, 410, 450, g_pImageQuit_Idle->_video,466, 113);
		_DrawBitmap(video, w, h, WINDOW_WIDTH/2 - 574/2, -30 - 6 *count, g_pImageBalerDown->_video,574, 365);
		_DrawBitmap(video, w, h, WINDOW_WIDTH/2 - 574/2, 350 + 6 *count, g_pImageBalerUp->_video,574, 365);
		count++;
		if(count > 40) CURRENT_SCREEN = MENU_STATE_OPTIONS;

	}

	else if(CURRENT_SCREEN == MENU_STATE_OPTIONS) {
		_DrawBitmap(video, w, h, WINDOW_WIDTH/2 - 574/2, -250, g_pImageBalerDown->_video,574, 365);
		_DrawBitmap(video, w, h, WINDOW_WIDTH/2 - 574/2, 570, g_pImageBalerUp->_video,574, 365);
		_DrawBitmap(video, w, h, 410, 150, g_pImageNewGame_Idle->_video,466, 113);
		_DrawBitmap(video, w, h, 410, 300, g_pImageOptions_Idle->_video,466, 113);
		_DrawBitmap(video, w, h, 410, 450, g_pImageQuit_Idle->_video,466, 113);

		if(Mouse::m_X >= 410 && Mouse::m_X <= 876 && Mouse::m_Y >= 150 && Mouse::m_Y <= 263)
			{	
			
			_DrawBitmap(video, w, h, 410, 150, g_pImageNewGame_Hover->_video,466, 113);
				if(Mouse::m_LeftButtonDown) {
					_PlaySoundEffect(0, 10, SOUND_OPTION_NO_MIXING);
					ShowGame(1);
				}

			}
		if(Mouse::m_X >= 410 && Mouse::m_X <= 876 && Mouse::m_Y >= 300 && Mouse::m_Y <= 413)
			{	
			
			_DrawBitmap(video, w, h, 410, 300, g_pImageOptions_Hover->_video,466, 113);
				if(Mouse::m_LeftButtonDown) {
					//ShowGame(2);
				}

			}
		if(Mouse::m_X >= 410 && Mouse::m_X <= 876 && Mouse::m_Y >= 450 && Mouse::m_Y <= 563)
			{	
			
			_DrawBitmap(video, w, h, 410, 450, g_pImageQuit_Hover->_video,466, 113);
				if(Mouse::m_LeftButtonDown) {
					exit(0);
				}

			}
	}
	_BalerAnimation._RunAnimations();
}

void MenuScene::Load()
{
	g_pImageCompany = _LoadImage(0, ".\\RESOURCES\\title_img_574x432.png", 574, 432);
	g_pImageNewGame_Idle = _LoadImage(4, ".\\RESOURCES\\new_game_466x113.png", 466, 113);
	g_pImageOptions_Idle = _LoadImage(4, ".\\RESOURCES\\options_466x113.png", 466, 113);
	g_pImageQuit_Idle = _LoadImage(4, ".\\RESOURCES\\quit_466x113.png", 466, 113);
	g_pImageNewGame_Hover = _LoadImage(4, ".\\RESOURCES\\new_game_HOVER_466x113.png", 466, 113);
	g_pImageOptions_Hover = _LoadImage(4, ".\\RESOURCES\\options_HOVER_466x113.png", 466, 113);
	g_pImageQuit_Hover = _LoadImage(4, ".\\RESOURCES\\quit_HOVER_466x113.png", 466, 113);
	g_pImageBalerDown = _LoadImage(4, ".\\RESOURCES\\smasher_down_574x365.png", 574, 365);
	g_pImageBalerUp = _LoadImage(4, ".\\RESOURCES\\smasher_up_574x365.png", 574, 365);
}

void MenuScene::Update()
{
}