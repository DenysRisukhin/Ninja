#include "Info.h"
#include "VirtualXmlReader.h"

Info::Info(Game* game, const path& filename)
	: _game(game)
	, _reader(new VirtualXmlReader(game->getDevice()->getFileSystem()->createXMLReader(filename)))
{
}

Info::Info(Game* game, IConfigReader* reader)
	: _game(game)
	, _reader(reader)
{
}

Info::~Info(void)
{
	delete _reader;
}

bool Info::next()
{
	bool result = _reader->next();
	if (result)
		OnNode(_reader->getNodeName());
	return result;
}