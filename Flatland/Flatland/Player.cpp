#include "Player.h"
#include "GameCore.h"

extern IMAGEINFO *g_pBackBuffer;

Player::Player(void)
{
	this->rect.x = 0;
	this->rect.y = 918;
	this->rect.w = 128;
	this->rect.h = 128;
	isShooting = false;
	_fTenFrame = 0.0;
	g_pCharacterCells2 = _LoadImage(0, ".\\RESOURCES\\walking01.png", 1280, 128);
	this->_PlayerAnimation._CreateAnimation("TEN_FRAME", &_fTenFrame, LINEAR, 0, 9.999, 0, 1, OPTION_REPEAT);
	acceleration = 1.0f;
	maxVelX = 10;
	jumpVel = -15;
	//redTapes = 5;
	invinCount = 0;
	upperOffX = 50;
	upperOffY = 5;
	
}

Player::~Player(void)
{
}

Rect Player::BoundingBox()
{
	Rect r(rect.x + 50, rect.y,rect.w - 100, rect.h);
	return r;
}

void Player::OneUp()
{
	if(redTapes < 5)
	{
		redTapes++;
	}
}

void Player::OneDown()
{
	if(invinCount <= 0)
	{
		redTapes--;
		invinCount = 15;
	}
}

void Player::Kill()
{
	redTapes = 0;
}

void Player::Draw(int upperX, int upperY)
{
	this->_PlayerAnimation._RunAnimations();

	int x = rect.x - upperX;
	int y = rect.y - upperY;
	if(movement == STOP)
	{
		if(facing == LEFT)
		{
			if(jump) DrawAlphaCellFlipped(x, y, g_pCharacterCells2->_video, 0, 0, rect.w, rect.h, 1280, 128);
			else DrawAlphaCellFlipped(x, y, g_pCharacterCells2->_video, 2, 0, rect.w, rect.h, 1280, 128);
		}
		else
		{
			if(jump) DrawAlphaCell(x, y, g_pCharacterCells2->_video, 0, 0, rect.w, rect.h, 1280, 128);
			else DrawAlphaCell(x, y, g_pCharacterCells2->_video, 2, 0, rect.w, rect.h, 1280, 128);
		}
	} 
	else if (movement == RIGHT)
	{
		int nFrame = 1 + _fTenFrame;
		if(jump) DrawAlphaCell(x, y, g_pCharacterCells2->_video, 0, 0, rect.w, rect.h, 1280, 128);
		else {
			DrawAlphaCell(x, y, g_pCharacterCells2->_video, _fTenFrame, 0, rect.w, rect.h, 1280, 128);
			if(nFrame == 1 || nFrame == 4 || nFrame == 7) {
				_PlaySoundEffect(0, 5 + (int)_fTenFrame/2, SOUND_OPTION_NO_MIXING);
			}
		}
	} 
	else 
	{
		int nFrame = 1 + _fTenFrame;
		if(jump) DrawAlphaCellFlipped(x, y, g_pCharacterCells2->_video, 0, 0, rect.w, rect.h, 1280, 128);
		else {
			DrawAlphaCellFlipped(x, y, g_pCharacterCells2->_video, _fTenFrame, 0, rect.w, rect.h, 1280, 128);
			if(nFrame == 1 || nFrame == 4 || nFrame == 7) {
				_PlaySoundEffect(0, 5 + (int)_fTenFrame/2, SOUND_OPTION_NO_MIXING);
			}
		}
	}
}

void Player::Update()
{
	if(Keyboard::k_UP || Keyboard::k_W)
	{
		if(velY == 0)
			Jump();
	}
	//if(Keyboard::k_DOWN || Keyboard::k_S) this->_PLAYER_STATE = _STATE_WALKING_SOUTH;
	if(Keyboard::k_RIGHT || Keyboard::k_D)
	{
		MoveRight();
	}
	if(Keyboard::k_LEFT || Keyboard::k_A)
	{
		MoveLeft();
	}

	if(Keyboard::k_SPACE)
	{
		isShooting = true;
	}

	if(!Keyboard::k_RIGHT && !Keyboard::k_LEFT && !Keyboard::k_A && !Keyboard::k_D) {
		StopMovement();
	}
	Move();

	if(invinCount > 0)
		invinCount--;
}