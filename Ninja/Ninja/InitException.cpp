#include "InitException.h"


InitException::InitException(const stringw& message): _message(message)
{
}

InitException::~InitException(void)
{
}

const stringw& InitException::getMessage() const
{
	return _message;
}