#pragma once

#include "Stage.h"
#include "LevelInfo.h"
#include "IController.h"

class Hud;
class Map;
class Player;
class Enemy;
class MovingController;

/**
* Represents game level. This is actually "game itself":
* board, obstacels, coins, main character, environment etc.
*/

/**
* 
*/

class Level : Stage 
{
public:

	/**
	* Initializes level using provided info.
	* @param game Game instance.
	* @param stage Contains path to config file.
	*/
	Level(Game* game, const StageConfig& stage);
	~Level(void);

	Game* getGame() const;

	Map* getBoard() const;
	Player* getMainCharacter() const;

	Hud* getHud();

	/**
	* Refreshes HUD and checks win and loss conditions.
	*/
	void refreshStatistics();

	virtual bool OnEvent(const irr::SEvent& event);

private:
	LevelInfo _config;

	Hud* _hud;
	Map* _board;
	Player* _player;
	irr::core::array<Enemy*> _enemies;

	//irr::core::array<IController*> _controllers;

	bool _paused;

	/**
	* Pauses or resumes level.
	*/
	void togglePaused();

	/**
	* Implementation of Stage.
	*/
	void update();
		
	/**
	* Helper for creating scene nodes for characters.
	*/
	irr::scene::IAnimatedMeshSceneNode* createNode(const LevelInfo::Model& model, irr::u32 position);

	/**
	* Helper for creating controllers for characters.
	*/
	//
	MovingController* createController(const LevelInfo::MovableController& config);

	void createCamera();
	void createBoard();
	void createMainCharacter();
	void createEnemies();

	void removeControllers();

	void removeCamera();
	void removeBoard();
	void removeMainCharacter();
	void removeEnemies();
};