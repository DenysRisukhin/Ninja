#include "HudInfo.h"

using namespace irr;
using namespace io;
using namespace core;
using namespace gui;
using namespace video;

HudInfo::HudInfo(Game* game, const path& filename) : Info(game, filename)
{
	while (next());
}

HudInfo::~HudInfo(void)
{
}

void HudInfo::OnNode(const stringw& name)
{
	if (name == "coinsCountLabel")
		readLabel(CoinsCountLabel);
	else if (name == "livesCountLabel")
		readLabel(LivesCountLabel);
	else if (name == "pauseIndicatorLabel")
		readLabel(PauseIndicatorLabel);
	else if (name == "pressAnyKeyIndicatorLabel")
		readLabel(PressAnyKeyIndicatorLabel);
	else if (name == "controlIndicatorLabel")
		readLabel(ControlIndicatorLabel);
	else if (name == "pathGameIndicatorLabel")
		readLabel(PathGameIndicatorLabel);
	else if (name == "developerIndicatorLabel")
		readLabel(DeveloperIndicatorLabel);
	else if (name == "engineIndicatorLabel")
		readLabel(EngineIndicatorLabel);
}

void HudInfo::readLabel(HudInfo::Label& label)
{
	label.Prefix = read<stringw>("prefix");

	label.X = read<s32>("x");
	label.Y = read<s32>("y");

	label.Width = read<u32>("width");
	label.Height = read<u32>("height");

	label.Font = read<IGUIFont*>("font");
	label.FontColor = read<SColor>("fontColor");
}