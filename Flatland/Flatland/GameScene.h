#pragma once
#include <list>

#include "scene.h"
#include "Player.h"
#include "Rat.h"
#include "bird.h"
#include "Projectile.h"
#include "paperBall.h"
#include "EnemyObject.h"
#include "Stationaries\building01.h"
#include "Stationaries\building02.h"
#include "Stationaries\cloud01.h"
#include "Stationaries\cloud02.h"
#include "Stationaries\door01.h"
#include "Stationaries\floorTile01.h"
#include "Stationaries\HP_Pickup.h"
#include "Stationaries\window01.h"
#include "Stationaries\table01.h"
#include "Stationaries\tree01.h"
#include "FireWall.h"
#include <time.h>

class GameScene :
	public Scene
{
public:
	GameScene(int level);
	~GameScene(void);
	virtual void Load();
	virtual void Draw(int *video, int w, int h);
	virtual void Update();
private:
	void LoadLevel1();
	void LoadLevel2();
	list<auto_ptr<MobileEntity>> mobs;
	list<auto_ptr<Couch>> backObj;
	list<auto_ptr<Couch>> frontObj;
	list<auto_ptr<Couch>> hpObj;
	list<auto_ptr<Rect>> geometry;
	list<auto_ptr<Rect>> instaDeath;
	list<auto_ptr<Projectile>> ballObj;
	Player player;
	int nextLevel;
	int timing;
	time_t curTime;
	Rect nextLevelRect;
	IMAGEINFO *g_pScenery;
	IMAGEINFO *g_pHealth;
	FireWall fireWall;
	bool eventArea;
	auto_ptr<Rect> eventRect;
};

