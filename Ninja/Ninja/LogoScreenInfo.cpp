#include "LogoScreenInfo.h"

using namespace irr;
using namespace core;
using namespace io;
using namespace video;

LogoScreenInfo::LogoScreenInfo(Game* game, const path& filename)
	: Info(game, filename)
{
	while (next());
}

LogoScreenInfo::~LogoScreenInfo(void)
{
}

void LogoScreenInfo::OnNode(const stringw& name)
{
	if (name == "logoScreen") {

		LogoTexture = read<ITexture*>("logoTexture");
		Duration = read<u32>("duration");
		ScaleTime = read<u32>("scaleTime");

	}
}