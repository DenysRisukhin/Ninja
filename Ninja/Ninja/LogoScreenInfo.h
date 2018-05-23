#pragma once

#include "Info.h"

class Game;

class LogoScreenInfo : Info
{
public:
	LogoScreenInfo(Game* game, const irr::io::path& filename);
	~LogoScreenInfo(void);

	irr::video::ITexture* LogoTexture;
	irr::u32 Duration;
	irr::u32 ScaleTime;

private:
	/*!
	Implementation of Config.
	*/
	void OnNode(const irr::core::stringw& name);
};