#pragma once

#include <irrlicht.h>
#include <irrKlang.h>
#include "StageConfig.h"
#include "GameEvent.h"

using namespace irrklang;
using namespace irr;
using namespace core;
using namespace io;
using namespace video;
using namespace gui;
using namespace scene;

class GameInfo;
class Hud;

/**
* The root object of the game.
*/

class Game : IEventReceiver {
public:

	/**
	* Initializes game using provided config.
	* @param configFilename Path to the config file.
	*/
	Game(const char* configFilename);

	~Game(void);

	virtual bool OnEvent(const SEvent& event);

	/**
	* Creates Irrlicht's root object using data from provided config
	* as well as IrrKlang's root object.
	*/
	void createDevice(const GameInfo& config);

	IrrlichtDevice* getDevice() const;

	ISoundEngine* getSoundEngine() const;

	void addMedia(const io::path& filename);

	/**
	* Broadcast event to all stages of the game.
	*/
	void broadcastEvent(GAME_EVENT event);

	/**
	* Updates game. Must be called until false is returned 
	* in order to run the game.
	*/
	bool update();

	/**
	* Converts Irrlicht's user event to the game event.
	* (Game events are broadcasted using Irrlicht's user event system.)
	*/
	static GAME_EVENT ToGameEvent(const SEvent& event);

	/**
	* Enables additional render: scene will be rendered twice per frame.
	* Special events shall be broadcasted before rendering additional 
	* time and after to allow stages to perform needed changes.
	*/
	void enableAdditionalRender(bool enable);

	void enableSound(bool enable);

private:

	Hud* _hud;

	IrrlichtDevice* _device;
	ISoundEngine* _soundEngine;

	array<irr::IEventReceiver*> _stages;

	u32 _sleepValue;
	bool _additionalRender;

	bool _soundEnabled;
	bool _soundAllowed;

	IEventReceiver* createStage(const StageConfig& stage);
};

