#pragma once

#include "Game.h"
#include "StageInfo.h"
#include "StageConfig.h"
#include "Sound.h"

/**
* Represents stage - high level building block for the game.
*/

class Stage : irr::IEventReceiver
{
public:
	
	/**
	* Initializes stage using provided info.
	* @param game Game instance.
	* @param stage Contains path to config file.
	* @param nodeName Name of node of config file with stage settings.
	*/
	Stage(Game* game, const StageConfig& stage, const irr::core::stringw& nodeName);
	~Stage(void);

	virtual bool OnEvent(const irr::SEvent& event);

	/**
	* Deactivates stage and broadcasts default deactivation event.
	*/
	void deactivate();

	/**
	* Deactivates stage and broadcasts specified deactivation event.
	* @param deactivationEvent Event to broadcast after deactivation.
	*/
	void deactivate(GAME_EVENT deactivationEvent);

protected:
	Game* _game;
	StageConfig _stageInfo;
	StageInfo _stageConfig;
	GAME_EVENT _deactivationEvent;

	irr::scene::ICameraSceneNode* _camera;
	irr::scene::ISceneNode* _rootNode;
	irr::gui::IGUIInOutFader* _fader;
	Sound* _backgroundSound;

	enum E_STATE
	{
		ES_INACTIVE,
		ES_FADING_IN,  // appeare
		ES_ACTIVE,
		ES_FADING_OUT  // disappeare
	} _state;

	void createOrthoCamera();
	void createBackground();

	/**
	* Called each frame if stage is active.
	* Should be implemented by descendants.
	*/
	virtual void update() = 0;

	/**
	* Returns true if provided event is in the set of activation events for this stage.
	* @param event Event to test.
	*/
	bool isActivationEvent(GAME_EVENT event);
};