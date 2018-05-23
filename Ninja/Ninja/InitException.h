#pragma once

#include <irrlicht.h>

using namespace irr;
using namespace core;

class InitException
{
public:
	InitException(const stringw& message);
	~InitException(void);

	const stringw& getMessage() const;

private:
	const stringw& _message;
};