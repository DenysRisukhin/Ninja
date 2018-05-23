#pragma once

#include "Stage.h"
#include "LogoScreenInfo.h"

/**
* Can be used for displaying both logo and splash screen.
* Logo screen can't be interrupted by user and splash screen lasts until user presses any key.
*/
class LogoScreen : Stage
{
public:
	
	/**
	* Initializes logo screen using provided info.
	* @param game Game instance.
	* @param stage Contains path to config file.
	*/
	LogoScreen(Game* game, const StageConfig& stage);
	~LogoScreen(void);

	virtual bool OnEvent(const irr::SEvent& event);

private:

	LogoScreenInfo _config;
	irr::scene::IMeshSceneNode* _node;
	irr::u32 _time;

	/**
	* Implementation of Stage.
	*/

	void update();
};