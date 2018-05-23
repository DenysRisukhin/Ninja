#pragma once

#include "Info.h"

class Game;

class HudInfo : Info
{
public:
	HudInfo(Game* game, const irr::io::path& filename);
	~HudInfo(void);

	struct Label
	{
		irr::s32 X;
		irr::s32 Y;
		irr::u32 Width;
		irr::u32 Height;
		irr::core::stringw Prefix;
		irr::gui::IGUIFont* Font;
		irr::video::SColor FontColor;
	};

	Label CoinsCountLabel;
	Label LivesCountLabel;
	Label PauseIndicatorLabel;
	Label PressAnyKeyIndicatorLabel;
	Label ControlIndicatorLabel;

	Label PathGameIndicatorLabel;
	Label DeveloperIndicatorLabel;
	Label EngineIndicatorLabel;
	;

private:

	void OnNode(const irr::core::stringw& name);

	void readLabel(Label& label);
};