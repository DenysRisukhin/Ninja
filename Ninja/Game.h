#pragma once

#include <irrlicht.h>
//#include "irrKlang\irrKlang.h"

#include <iostream>
#include <time.h>
#include <vector>

#include "Terrain.h"
#include "Player.h"
#include "Camera.h"
#include "EventReciever.h"
#include "Skybox.h"
#include "PowerBall.h"
#include "BadFaerie.h"
#include "BadNinja.h"
#include "Monster.h"
#include "Wraith.h"
#include "GameHud.h"
#include "HealthPickup.h"
#include "Coin.h"

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
//#pragma comment(lib, "irrKlang.lib")
#endif

#define DEBUG

using namespace std;
using namespace irr;
//using namespace irrklang;
using namespace core;
using namespace video;
using namespace scene;
using namespace io;
using namespace gui;

class Game
{
public:
	Game();

	// Function to handle user input.
	void processInput(IrrlichtDevice*, ISceneManager*, IVideoDriver*, ITriangleSelector*, EventReciever*, Player*, Camera*, f32);
	void handleCollisions(Player*, Camera*, f32);
	void handleCollisionWithPlayer(Player*, Camera*, f32);
	void handleCollisionEnemyPowerBall(void);
	void handleCollisionBetweenEnemies(GameObject*);
	bool collisionsBetweenEnemyAndBalls(ISceneNode*);
	void collisionBetweenFaerieAndPlayer(Player*, Camera*, ISceneNode*, f32);
	void updateGameObjects(f32);
	void handleGameState(GameState &, Player*, IrrlichtDevice*, ISceneManager*, IVideoDriver*);
	void displayGameOverScreen(IVideoDriver*, IGUIEnvironment*);
	void displayGameCompleteScreen(IVideoDriver*, IGUIEnvironment*);
	void initiateWave0(Player*, IrrlichtDevice*, ISceneManager*, IVideoDriver*);
	void initiateWave1(Player*, IrrlichtDevice*, ISceneManager*, IVideoDriver*);
	void initiateWave2(Player*, IrrlichtDevice*, ISceneManager*, IVideoDriver*);
	void initiateWave3(Player*, IrrlichtDevice*, ISceneManager*, IVideoDriver*);
	void initiateWave4(Player*, IrrlichtDevice*, ISceneManager*, IVideoDriver*);
	void initiateWave5(Player*, IrrlichtDevice*, ISceneManager*, IVideoDriver*);
	void updateWaveStatus(GameState &, IrrlichtDevice*, Player*, ISceneManager*, IVideoDriver*);
	void pushEnemies(Player*);
	void spawnBadNinja(Player* player, IrrlichtDevice* device, ISceneManager* smgr, IVideoDriver* driver, vector3df coinPos);
	void spawnBadFaerie(Player*, IrrlichtDevice*, ISceneManager*, IVideoDriver*);
	void spawnMonster(Player*, IrrlichtDevice*, ISceneManager*, IVideoDriver*);
	void spawnWraith(Player*, IrrlichtDevice*, ISceneManager*, IVideoDriver*);
	void displayMainMenu(GameState &, IrrlichtDevice*);
	f32 getLastUpdate();
	void setLastUpdate(f32 update);
	u8 getNumOfEnemies();
	
	bool gamePaused;

	std::vector<BadNinja *> vecBadNinja;
	list<Coin*> listCoin;

private:
	list<GameObject*> updateList;
	f32 lastUpdate;
	f32 timeSinceStart;
	ITriangleSelector* selector;
	u32 delayTimer;
	BadFaerie* badFaerie;
	Monster* monster;
	Wraith* wraith;
	HealthPickup * pickup_0, *pickup_1;
	
	bool bMainMenuDisplayed;
	bool bGameOverDisplayed;
	bool bGameCompleteDisplayed;
	Enemy* enemies[20];
	u8 numOfEnemies;

	bool bWave0Finished;
	bool bWave1Finished;
	bool bWave2Finished;
	bool bWave3Finished;
	bool bWave4Finished;
	bool bWave5Finished;

	bool bWave0Started;
	bool bWave1Started;
	bool bWave2Started;
	bool bWave3Started;
	bool bWave4Started;
	bool bWave5Started;

};

