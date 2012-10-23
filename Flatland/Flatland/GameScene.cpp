#include "GameScene.h"
#include "Stationaries\Assets.h"
#include <math.h>

extern TEXTUREINFO *g_pBackBuffer;
IMAGEINFO *g_test;

bool fire = false;

GameScene::GameScene(int level)
{
	//g_pScenery = _LoadImage(3, ".\\RESOURCES\\backdrop_6560.x1440.png", 6560, 1440);
	eventArea = false;
	switch(level)
	{
	case 1:
		LoadLevel1();
		break;
	case 2:
		LoadLevel2();
		break;
	}
	g_pHealth = _LoadImage(0, ".\\RESOURCES\\Health.png", 30, 32);
	g_test = _LoadImage(0, ".\\RESOURCES\\flame01.png", 360, 1440);
}


GameScene::~GameScene(void)
{

}

void GameScene::LoadLevel1()
{	
	g_pScenery = _LoadImage(3, ".\\RESOURCES\\backdrop_6560.x1440.png", 6560, 1440);
	mobs.push_back(auto_ptr<MobileEntity>(new BirdObject(1300,800)));
	mobs.push_back(auto_ptr<MobileEntity>(new RatObject(4760,510)));
	mobs.push_back(auto_ptr<MobileEntity>(new RatObject(3575,600)));
	mobs.push_back(auto_ptr<MobileEntity>(new RatObject(6100,600)));
	mobs.push_back(auto_ptr<MobileEntity>(new EnemyObject(1366,600)));
	mobs.push_back(auto_ptr<MobileEntity>(new EnemyObject(2640,600)));
	mobs.push_back(auto_ptr<MobileEntity>(new EnemyObject(5360,600)));
	frontObj.push_back(auto_ptr<Couch>(new Door01(180,938)));
	frontObj.push_back(auto_ptr<Couch>(new Building01(0,618)));
	frontObj.push_back(auto_ptr<Couch>(new Bridge01(4571,773)));

	hpObj.push_back(auto_ptr<Couch>(new HP_Pickup(1000, 750)));

	geometry.push_back(auto_ptr<Rect>(new Rect(0,1061,3009,397)));
	geometry.push_back(auto_ptr<Rect>(new Rect(3229,1061,680,397)));
	geometry.push_back(auto_ptr<Rect>(new Rect(4094,1061,481,397)));
	geometry.push_back(auto_ptr<Rect>(new Rect(6143,1061,417,397)));
	geometry.push_back(auto_ptr<Rect>(new Rect(4575,1061,1568,27)));

	geometry.push_back(auto_ptr<Rect>(new Rect(1919,996,64,70)));
	geometry.push_back(auto_ptr<Rect>(new Rect(1983,932,64,134)));
	geometry.push_back(auto_ptr<Rect>(new Rect(2047,868,64,200)));

	geometry.push_back(auto_ptr<Rect>(new Rect(2880,996,64,200)));
	geometry.push_back(auto_ptr<Rect>(new Rect(2944,932,64,200)));
	geometry.push_back(auto_ptr<Rect>(new Rect(2114,1000,64,200)));

	geometry.push_back(auto_ptr<Rect>(new Rect(3232,932,64,200)));
	geometry.push_back(auto_ptr<Rect>(new Rect(3296,996,64,200)));

	instaDeath.push_back(auto_ptr<Rect>(new Rect(3009,1215,220,225)));
	instaDeath.push_back(auto_ptr<Rect>(new Rect(3909,1215,185,225)));

	nextLevel = 2;
	nextLevelRect = Rect(6360, 0, 200, 1440);

	if(fire)
	{
		player.setX(LEVEL_LENGTH - 960);
		nextLevel = -1;
		nextLevelRect = Rect(0,0,200,1440);
	}
}

void GameScene::LoadLevel2()
{
	g_pScenery = _LoadImage(3, ".\\RESOURCES\\backdrop2_6360.x1440.png", 6560, 1440);

	mobs.push_back(auto_ptr<MobileEntity>(new EnemyObject(430,600)));
	mobs.push_back(auto_ptr<MobileEntity>(new EnemyObject(2300,600)));
	mobs.push_back(auto_ptr<MobileEntity>(new EnemyObject(3500,600)));
	mobs.push_back(auto_ptr<MobileEntity>(new RatObject(1150,510)));
	mobs.push_back(auto_ptr<MobileEntity>(new RatObject(4400,510)));
	mobs.push_back(auto_ptr<MobileEntity>(new RatObject(1260,1240)));
	mobs.push_back(auto_ptr<MobileEntity>(new RatObject(1830,1210)));
	mobs.push_back(auto_ptr<MobileEntity>(new RatObject(2437,1210)));

	geometry.push_back(auto_ptr<Rect>(new Rect(0,845,698,742)));

	//underground
	geometry.push_back(auto_ptr<Rect>(new Rect(698,1299,189,141)));
	geometry.push_back(auto_ptr<Rect>(new Rect(982,1299,514,141)));
	geometry.push_back(auto_ptr<Rect>(new Rect(1145,1245,236,141)));
	geometry.push_back(auto_ptr<Rect>(new Rect(1576,1299,104,141)));
	geometry.push_back(auto_ptr<Rect>(new Rect(1680,1215,378,225)));
	geometry.push_back(auto_ptr<Rect>(new Rect(2168,1215,360,225)));
	geometry.push_back(auto_ptr<Rect>(new Rect(2528,1087,351,353)));
	geometry.push_back(auto_ptr<Rect>(new Rect(2879,950,41,490)));
	geometry.push_back(auto_ptr<Rect>(new Rect(2920,845,3640,742)));

	//above ground
	geometry.push_back(auto_ptr<Rect>(new Rect(823,845,969,211)));
	geometry.push_back(auto_ptr<Rect>(new Rect(1792,845,352,147)));
	geometry.push_back(auto_ptr<Rect>(new Rect(2144,845,256,62)));
	geometry.push_back(auto_ptr<Rect>(new Rect(2400,845,352,51)));

	//Crate and Barrel
	geometry.push_back(auto_ptr<Rect>(new Rect(158,785,64,64)));
	geometry.push_back(auto_ptr<Rect>(new Rect(637,785,64,64)));
	geometry.push_back(auto_ptr<Rect>(new Rect(855,676,40,32)));
	geometry.push_back(auto_ptr<Rect>(new Rect(843,481,40,32)));
	geometry.push_back(auto_ptr<Rect>(new Rect(843,321,40,32)));
	geometry.push_back(auto_ptr<Rect>(new Rect(651,576,40,32)));
	geometry.push_back(auto_ptr<Rect>(new Rect(651,409,40,32)));
	geometry.push_back(auto_ptr<Rect>(new Rect(651,226,40,32)));
	geometry.push_back(auto_ptr<Rect>(new Rect(1483,262,40,32)));

	//rooftops
	geometry.push_back(auto_ptr<Rect>(new Rect(310,148,357,32)));
	geometry.push_back(auto_ptr<Rect>(new Rect(866,269,357,32)));
	geometry.push_back(auto_ptr<Rect>(new Rect(1212,384,244,32)));
	geometry.push_back(auto_ptr<Rect>(new Rect(1508,148,357,32)));
	geometry.push_back(auto_ptr<Rect>(new Rect(1904,469,356,32)));

	instaDeath.push_back(auto_ptr<Rect>(new Rect(887,1400,96,40)));
	instaDeath.push_back(auto_ptr<Rect>(new Rect(1495,1350,81,90)));
	instaDeath.push_back(auto_ptr<Rect>(new Rect(2056,1380,112,60)));

	player.setY(845 - 130);

	eventArea = true;
	eventRect = auto_ptr<Rect>(new Rect(5600, 0, 200, 1440));
}

void GameScene::Load()
{
}

void GameScene::Update()
{
	_PlaySoundEffect(0, 10, SOUND_OPTION_NO_MIXING);
	bool alive = true;
	curTime = time(NULL);
	timing = curTime;
	player.Update();
	player.handleGeo(geometry);
	Rect box = player.BoundingBox();
	for(auto i = mobs.begin(); i != mobs.end() ; )
	{
		(*i)->Update();
		(*i)->handleGeo(geometry);
		//check collision
		if((*i)->BoundingBox().Intersects(box))
		{
			if((*i)->BoundingBox().y > (box.y + box.h - 15))
			{
				_PlaySoundEffect(0, 2);
				mobs.erase(i++);
			}
			else
			{
				i++;
				player.OneDown();
				_PlaySoundEffect(0, 4, SOUND_OPTION_NO_MIXING);
			}
		} 
		else 
		{
			i++;
		}
	}
	for(auto i = ballObj.begin(); i != ballObj.end(); )
	{
		(*i)->Update();
		(*i)->handleGeo(geometry);
		//check collision
		for(auto j = mobs.begin(); j != mobs.end() ; )
		{
			if((*j)->BoundingBox().Intersects((*i)->BoundingBox()))
			{
				_PlaySoundEffect(0, 2);
				mobs.erase(j++);
			}
			else
			{
				j++;
			}
		}
		if((*i)->deathtime < timing)
		{
			ballObj.erase(i++);
		}
		else
		{
			i++;
		}
	}
	for(auto i = instaDeath.begin(); i != instaDeath.end(); i++)
	{
		if((*i)->Intersects(player.BoundingBox()))
			player.Kill();
	}

	for(auto i = hpObj.begin(); i != hpObj.end(); )
	{
		if((*i)->rect.Intersects(player.BoundingBox()) && player.getLife() != 5)
		{
			player.OneUp();
			hpObj.erase(i++);
		}
		else
		{
			i++;
		}
	}

	if(fire)
	{
		fireWall.Update();
		if(fireWall.BoundingBox().Intersects(player.BoundingBox()))
			player.Kill();
	}

	if(eventArea && !fire)
	{
		if(eventRect->Intersects(player.BoundingBox()))
		{
			fire = true;
			_PlaySoundEffect(0, 11);
			nextLevel = 1;
			nextLevelRect = Rect(0, 0, 200, 1440);
		}
	}
	if(player.isShooting)
	{
		player.isShooting=false;
		//killstuff
		ballObj.push_back(auto_ptr<Projectile>(new paperBall(player.getX(), player.getY())));
	}
	if(player.isDead()) {
		_StopSoundEffect(0, 10);
		_StopSoundEffect(0, 11);
		ShowGameOver();
	}
	else if(nextLevel > 0)
	{
		if(nextLevelRect.Intersects(player.BoundingBox()))
			ShowGame(nextLevel);
	}
	else if(nextLevel == -1)
	{
		if(nextLevelRect.Intersects(player.BoundingBox()))
			ShowEnding();
	}
}

void GameScene::Draw(int *video, int w, int h)
{
	Rect rect = player.BoundingBox();
	int upperX = rect.x + rect.w/2 - WINDOW_WIDTH/2;
	int upperY = rect.y + rect.h/2 - WINDOW_HEIGHT/2;

	if((upperX) < 0 )
		upperX = 0;

	if(upperX + WINDOW_WIDTH > LEVEL_LENGTH)
		upperX = LEVEL_LENGTH - WINDOW_WIDTH - 1;

	if(upperY < 0 )
		upperY = 0;

	if(upperY + WINDOW_HEIGHT > LEVEL_HEIGHT)
		upperY = LEVEL_HEIGHT - WINDOW_HEIGHT - 1;

	_DrawBitmapOffset(video, w, h, 0, 0,WINDOW_WIDTH, WINDOW_HEIGHT, g_pScenery->_video,upperX,upperY, 6560, 1440);

	for(auto i = backObj.begin(); i != backObj.end() ; i++)
	{
		(*i)->Draw(video, w, h, upperX, upperY);
	}

	for(auto i = hpObj.begin(); i != hpObj.end() ; i++)
	{
		(*i)->Draw(video, w, h, upperX, upperY);
	}

	for(auto i = mobs.begin(); i != mobs.end() ; i++)
	{
		(*i)->Draw(upperX,upperY);
	}

		for(auto i = ballObj.begin(); i != ballObj.end() ; i++)
	{
		(*i)->Draw(upperX,upperY);
	}

	player.Draw(upperX,upperY);

	for(auto i = frontObj.begin(); i != frontObj.end() ; i++)
	{
		(*i)->Draw(video, w, h, upperX, upperY);
	}

	int redTapes = player.getLife();
	int x = 10;
	int y = 10;
	for (int t=0; t<redTapes; t++)
	{
		_DrawAlphaBitmap(video, w, h,x,y, g_pHealth->_video,30,32);
		x += 40;
	}
	if(fire)
	{
		fireWall.Draw(upperX, upperY);
	}
	//_DrawAlphaBitmap(video, w, h, 0, 0, g_test->_video, 360, 1440);
}