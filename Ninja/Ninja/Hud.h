#pragma once

#include "HudInfo.h"

class Game;
class Level;

/**
* Represents heads-up display: set of labels.
*/

class Hud : irr::IEventReceiver
{
public:
	
	/**
	* It is important to call activate/deactivate before/after use of HUD.
	* @param level Level instance.
	* @param configFilename Path to config file.
	*/
	Hud(Level* level, const irr::io::path& configFilename);

	~Hud(void);

	/**
	* Activates HUD (prepares UI & rendering pipeline).
	*/
	void activate();

	/**
	* Deactivates HUD (affects UI & rendering pipeline).
	*/
	void deactivate();

	/**
	* Makes HUD visible or invisible depending on argument.
	* @param show Visibility flag.
	*/
	void show(bool show);

	void setLivesCount(irr::u32 count);
	void setCoinsCount(irr::u32 count);

	void showPauseIndicator(bool show);
	void showPressAnyKeyIndicator(bool show);
	void showControlLabel(bool show);

	void showSoundLogo(bool show);
	void showAboutLabels(bool show);
	void showPathGameLabel(bool show);

	bool OnEvent(const irr::SEvent& event);

private:

	IGUIImage *soundLogo;
	IGUIImage *healthLogo;
	IGUIImage *moneyLogo;

	Game* _game;
	HudInfo _config;

	irr::gui::IGUIStaticText* _livesCountLabel;
	irr::gui::IGUIStaticText* _coinsCountLabel;
	irr::gui::IGUIStaticText* _pauseIndicatorLabel;

	irr::gui::IGUIStaticText* _pressAnyKeyIndicatorLabel;
	irr::gui::IGUIStaticText* _controlIndicatorLabel;

	irr::gui::IGUIStaticText* _pathGameIndicatorLabel;
	irr::gui::IGUIStaticText* _developerIndicatorLabel;
	irr::gui::IGUIStaticText* _engineIndicatorLabel;

	bool _pauseIndicated;

	irr::scene::ICameraSceneNode* _previousCamera;

	void createLabel(irr::gui::IGUIStaticText** label, const HudInfo::Label& config);
};