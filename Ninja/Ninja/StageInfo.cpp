#include "StageInfo.h"

using namespace irr;
using namespace core;
using namespace io;
using namespace video;

StageInfo::StageInfo(Game* game, const path& filename, const stringw& nodeName): Info(game, filename), _nodeName(nodeName)
{
	while (next());
}

StageInfo::~StageInfo(void)
{
}

void StageInfo::OnNode(const stringw& name)
{
	if (name == _nodeName) {

		BackgroundTexture = read<ITexture*>("backgroundTexture");
		FadeTime = read<u32>("fadeTime");

		DefaultDeactivationEvent = (GAME_EVENT)read<u32>("defaultDeactivationEvent");

		BackgroundSoundFilename = read<path>("backgroundSound");
		LoopBackgroundSound = read<bool>("loopBackgroundSound");
	}
	else if (name == "activationEvent") {

		ActivationEvents.push_back((GAME_EVENT)read<u32>("value"));

	}
}