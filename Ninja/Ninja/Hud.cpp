#include "Hud.h"
#include "Game.h"
#include "Level.h"
#include "Map.h"

using namespace irr;
using namespace core;
using namespace io;
using namespace gui;
using namespace video;
using namespace scene;

static const f32 MIN_OPACITY = 0.01f;


Hud::Hud(Level* level, const path& configFilename) : _game(level->getGame())
, _config(_game, configFilename)
, _pauseIndicated(false)
{
	createLabel(&_livesCountLabel, _config.LivesCountLabel);
	createLabel(&_coinsCountLabel, _config.CoinsCountLabel);
	createLabel(&_pauseIndicatorLabel, _config.PauseIndicatorLabel);

	//
	createLabel(&_pressAnyKeyIndicatorLabel, _config.PressAnyKeyIndicatorLabel);
	createLabel(&_controlIndicatorLabel, _config.ControlIndicatorLabel);

	//
	createLabel(&_pathGameIndicatorLabel, _config.PathGameIndicatorLabel);

	//
	createLabel(&_developerIndicatorLabel, _config.DeveloperIndicatorLabel);
	createLabel(&_engineIndicatorLabel, _config.EngineIndicatorLabel);

	IrrlichtDevice* device = _game->getDevice();
	ISceneManager* scene = device->getSceneManager();
	auto video = device->getVideoDriver();
	auto gui = device->getGUIEnvironment();

	soundLogo = gui->addImage(video->getTexture("C:/Den/Programming/TestProjects/PathGame/PathGameDemo/PathGame/Media/Images/vol.png"), core::position2d<int>(380, 15));
	soundLogo->setVisible(false);


	healthLogo = gui->addImage(video->getTexture("C:/Den/Programming/TestProjects/PathGame/PathGameDemo/PathGame/Media/Images/heart.png"), core::position2d<int>(925, 65));


	moneyLogo = gui->addImage(video->getTexture("C:/Den/Programming/TestProjects/PathGame/PathGameDemo/PathGame/Media/Images/moneyIcon.png"), core::position2d<int>(910, 0));


	show(false);
}

void Hud::showAboutLabels(bool show) {
	_developerIndicatorLabel->setVisible(show);
	_engineIndicatorLabel->setVisible(show);
}

void Hud::showPathGameLabel(bool show) {
	_pathGameIndicatorLabel->setVisible(show);
}

void Hud::showControlLabel(bool show) {
	_controlIndicatorLabel->setVisible(show);
}

void Hud::showSoundLogo(bool show) {
	soundLogo->setVisible(show);
}

Hud::~Hud(void)
{
	if (soundLogo)
	{

		soundLogo->remove();
		soundLogo = NULL;
	}

	if (healthLogo)
	{
		healthLogo->remove();
		healthLogo = NULL;
	}

	if (moneyLogo)
	{
		moneyLogo->remove();
		moneyLogo = NULL;
	}

}

void Hud::activate()
{
	_previousCamera = _game->getDevice()->getSceneManager()->getActiveCamera();
	show(true);
}

void Hud::deactivate()
{
	_game->enableAdditionalRender(false);
	show(false);
}

void Hud::show(bool show)
{
	_livesCountLabel->setVisible(show);
	_coinsCountLabel->setVisible(show);
	_pauseIndicatorLabel->setVisible(show && _pauseIndicated);
	healthLogo->setVisible(show);
	moneyLogo->setVisible(show);
	//_controlIndicatorLabel->setVisible(show);
	//_pressAnyKeyIndicatorLabel->setVisible(show);
}

void Hud::setLivesCount(u32 count)
{
	_livesCountLabel->setText((_config.LivesCountLabel.Prefix + stringw(count)).c_str());
}

void Hud::setCoinsCount(u32 count)
{
	_coinsCountLabel->setText((_config.CoinsCountLabel.Prefix + stringw(count)).c_str());
}

void Hud::showPauseIndicator(bool show)
{
	_pauseIndicatorLabel->setVisible((_pauseIndicated = show) && _livesCountLabel->isVisible());
}

void Hud::showPressAnyKeyIndicator(bool show)
{
	_pressAnyKeyIndicatorLabel->setVisible(show);
}

bool Hud::OnEvent(const SEvent& event)
{

	ISceneManager* scene;
	IVideoDriver* video;

	switch (Game::ToGameEvent(event)) {

	case GE_ADDITIONAL_RENDER_STARTING:
		scene = _game->getDevice()->getSceneManager();
		video = _game->getDevice()->getVideoDriver();

		_previousCamera = scene->getActiveCamera();

		show(false);
		break;

	case GE_ADDITIONAL_RENDER_FINISHED:
		scene = _game->getDevice()->getSceneManager();
		video = _game->getDevice()->getVideoDriver();

		scene->setActiveCamera(_previousCamera);
		video->setRenderTarget(NULL);

		show(true);
		break;

	}

	return false;
}

void Hud::createLabel(IGUIStaticText** label, const HudInfo::Label& config)
{
	*label = _game->getDevice()->getGUIEnvironment()->addStaticText(
		config.Prefix.c_str(), rect<s32>(vector2d<s32>(config.X, config.Y),
			dimension2du(config.Width, config.Height)), false, false);

	IGUIStaticText& text = **label;

	text.setOverrideFont(config.Font);
	text.setOverrideColor(config.FontColor);
	text.setTextAlignment(EGUIA_UPPERLEFT, EGUIA_CENTER);
	text.setVisible(false);
}