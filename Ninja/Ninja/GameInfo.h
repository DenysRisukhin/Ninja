#pragma once

#include "Info.h"
#include "StageInfo.h"

using namespace irr;
using namespace core;
using namespace io;
using namespace video;

class Game;

class GameInfo : Info
{
public:
	/*!
	Reads settings from provided file.
	@param game Game instance.
	@param filename Path to file with settings.
	*/
	GameInfo(Game* game, const char* filename);

	/*!
	Screen config.
	*/
	struct
	{
		E_DRIVER_TYPE DriverType;
		u32 Width;
		u32 Height;
		u32 Bpp;
		bool Windowed;
		stringw Caption;
	} Screen;

	struct
	{
		/*!
		Determines how long game will do nothing after each frame.
		Influences maximal FPS (FPS <= 1/Sleep).
		*/
		u32 Sleep;
	} Performance;

	/*!
	Info about each stage of the game.
	*/
	array<StageConfig> Stages;

private:
	/*!
	Implementation of Config.
	*/
	void OnNode(const stringw& name);
};