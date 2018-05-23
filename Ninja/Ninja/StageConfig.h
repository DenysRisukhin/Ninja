#pragma once

#include <irrlicht.h>
#include "StageType.h"

struct StageConfig
{
	STAGE_TYPE Type;
	irr::core::stringw ConfigFilename;
};
