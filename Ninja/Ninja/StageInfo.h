#pragma once

#include "Info.h"
#include "StageType.h"
#include "GameEvent.h"

class Game;

class StageInfo : Info
{
public:
	StageInfo(Game* game, const irr::io::path& filename,
		const irr::core::stringw& nodeName);
	~StageInfo(void);

	/*!
	When any of these events is happened
	stage should be started (activated).
	*/
	irr::core::array<GAME_EVENT> ActivationEvents;

	/*!
	Event that should be broadcasted when stage
	has been deactivated (finished).
	*/
	GAME_EVENT DefaultDeactivationEvent;

	irr::video::ITexture* BackgroundTexture;
	irr::u32 FadeTime;

	irr::io::path BackgroundSoundFilename;
	bool LoopBackgroundSound;

private:
	irr::core::stringw _nodeName;

	/*!
	Implementation of Config.
	*/
	void OnNode(const irr::core::stringw& name);
};