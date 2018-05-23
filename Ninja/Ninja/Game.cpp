#include "Game.h"

#include "GameInfo.h"
#include "InitException.h"
//#include "NotImplementedException.h"
#include "LogoScreen.h"
#include "Menu.h"
#include "Level.h"
#include "Hud.h"

Game::Game(const char* configFilename)
	: _device(NULL)
	, _additionalRender(false)
{
	// reads config and forces game instance to create device
	GameInfo config(this, configFilename);
	_sleepValue = 0;// config.Performance.Sleep;

	// creates stages (стянули с info.xml в массив Stages (харанит структуру StageConfig) все остальные имена .xml и номер для каждого xml.)
	
	_stages.reallocate(config.Stages.size());
	// кладем stages в _stages их 10 или 11
	for (int i = 0; i < (int)config.Stages.size(); ++i)
		_stages.push_back(createStage(config.Stages[i]));

	_soundAllowed = true;

	broadcastEvent(GE_GAME_STARTED);
}

Game::~Game(void)
{
	for (u32 i = 0; i < _stages.size(); ++i)
		delete _stages[i];
	_soundEngine->drop();
	_device->drop();
}

bool Game::OnEvent(const SEvent& event)
{
	// processes important events out of turn
	switch (ToGameEvent(event)) {

	case GE_GAME_LOGO_FINISHED:
		_hud->showPressAnyKeyIndicator(true);
		_hud->showPathGameLabel(true);
		break;

	case GE_SPLASH_SCREEN_FINISHED:
		_hud->showPressAnyKeyIndicator(false);
		_hud->showSoundLogo(true);
		_hud->showPathGameLabel(false);
		break;

	case GE_LEVEL_SUCCEEDED:
		_hud->showPressAnyKeyIndicator(true);
		break;

	case GE_LEVEL_FAILED:
		_hud->showPressAnyKeyIndicator(true);
		break;

	case GE_SOUND_MENU_REQUESTED:
		_hud->showSoundLogo(true);
		break;

	case GE_SUCCESS_SCREEN_FINISHED:
		_hud->showPressAnyKeyIndicator(false);
		break;

	case GE_FAILURE_SCREEN_FINISHED:
		_hud->showPressAnyKeyIndicator(false);
		break;

	case GE_HELP_SCREEN_FINISHED:
		_hud->showPressAnyKeyIndicator(false);
		_hud->showControlLabel(false);
		break;

	case GE_ABOUT_SCREEN_FINISHED:
		_hud->showPressAnyKeyIndicator(false);
		_hud->showAboutLabels(false);
		break;

	case GE_ABOUT_REQUESTED:
		_hud->showAboutLabels(true);
		_hud->showPressAnyKeyIndicator(true);
		break;

	case GE_HELP_REQUESTED:
		_hud->showControlLabel(true);
		_hud->showPressAnyKeyIndicator(true);
		break;

	case GE_SOUND_ON:
		enableSound(_soundAllowed = true);
		_hud->showSoundLogo(false);
		break;

	case GE_SOUND_OFF:
		enableSound(_soundAllowed = false);
		_hud->showSoundLogo(false);
		break;

	case GE_EXIT_REQUESTED:
		broadcastEvent(GE_GAME_FINISHED);
		break;

	case GE_GAME_FINISHED:
		_device->closeDevice();
		break;
	}

	// lets each stage to process current event
	for (u32 i = 0; i < _stages.size(); ++i)
		if (_stages[i]->OnEvent(event))
			return true;

	return false;
}

void Game::createDevice(const GameInfo& config)
{
	// creates Irrlicht's device
	if (!_device)
		_device = ::createDevice(config.Screen.DriverType, dimension2d<u32>(config.Screen.Width, config.Screen.Height), config.Screen.Bpp, !config.Screen.Windowed, false, false, this);
	if (!_device)
		throw InitException("_device");

	// common settings
	_device->setWindowCaption(config.Screen.Caption.c_str());
	_device->getSceneManager()->setAmbientLight(SColorf(SColor(0xFFFFFFFF)));

	// creates IrrKlang's sound engine
	_soundEngine = createIrrKlangDevice();
	if (!_soundEngine)
		throw InitException("_soundEngine");
}

IrrlichtDevice* Game::getDevice() const
{
	return _device;
}

irrklang::ISoundEngine* Game::getSoundEngine() const
{
	return _soundEngine;
}

void Game::addMedia(const path& path)
{
	_device->getFileSystem()->addFileArchive(path);
}

void Game::broadcastEvent(GAME_EVENT event)
{
	SEvent userEvent;

	userEvent.EventType = EET_USER_EVENT;
	userEvent.UserEvent.UserData1 = event;

	OnEvent(userEvent);
}

bool Game::update()
{
	bool result = _device->run();
	if (result) {
		if (_device->isWindowActive()) {

		/*	if (_soundAllowed)
				enableSound(true);
			else*/
				enableSound(true);


			IVideoDriver* video = _device->getVideoDriver();
			IGUIEnvironment* gui = _device->getGUIEnvironment();
			ISceneManager* scene = _device->getSceneManager();

			video->beginScene();

			if (_additionalRender) {
				broadcastEvent(GE_ADDITIONAL_RENDER_STARTING);
				scene->drawAll();
				gui->drawAll();
				broadcastEvent(GE_ADDITIONAL_RENDER_FINISHED);
			}

			scene->drawAll();
			gui->drawAll();

			// prepares next frame while current is being rendered by the GPU
			broadcastEvent(GE_FRAME_ENDED);

			video->endScene();

			// prevents excessive CPU usage
			// (do we need 1000 FPS? I don't think so,
			// as for me, 60 is enough)
			if (_sleepValue)
				_device->sleep(_sleepValue);
		}
		// prevents CPU usage if window is not active 
		// (user switched to another one and is not playing)
		else {
			enableSound(false);
			_device->yield();
		}
	}
	return result;
}

GAME_EVENT Game::ToGameEvent(const SEvent& event)
{
	return event.EventType == EET_USER_EVENT ? (GAME_EVENT)event.UserEvent.UserData1 : GE_NULL;
}

void Game::enableAdditionalRender(bool enable)
{
	_additionalRender = enable;
}

void Game::enableSound(bool enable)
{
	if (!_soundAllowed && enable)
		return;

	if (_soundEnabled != enable)
		_soundEngine->setSoundVolume(_soundEnabled = enable ? 1 : 0);

	//if (enable == true) {
	////	//_soundEnabled = true;
	////	//_soundAllowed = true;
	//	_soundEngine->setSoundVolume(1.0);
	//////	_soundEngine->
	//}
	//else {
	////	//_soundEnabled = false;
	////	//_soundAllowed = false;
	////	////_soundEngine->setSoundVolume(false);
	////	//_soundEngine->stopAllSounds();
	//	_soundEngine->setSoundVolume(0.0);
	//}
}

IEventReceiver* Game::createStage(const StageConfig& stage)
{
	switch (stage.Type) {

		case ST_LOGO:
			return (IEventReceiver*) new LogoScreen(this, stage);

		case ST_MENU:
			return (IEventReceiver*) new Menu(this, stage);

		case ST_LEVEL: {
			auto level = new Level(this, stage);
			_hud = level->getHud();
			return (IEventReceiver*)level;
		}
				   //default:
				   //throw NotImplementedException();
	}
}