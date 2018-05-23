#pragma once

#include "IConfigReader.h"
#include <irrlicht.h>

/**
* Represents xml reader that does not use Irrlicht's filesystem.
*/
class XmlReader : public IConfigReader
{
public:
	XmlReader(const char* filename);
	~XmlReader(void);

	/**
	* Implementation of the IConfigReader.
	*/
	
	virtual bool next();

	virtual irr::core::stringw getNodeName();

	virtual irr::core::stringw getAttributeValue(const irr::core::stringw& name);
	virtual int getAttributeValueAsInt(const irr::core::stringw& name);
	virtual float getAttributeValueAsFloat(const irr::core::stringw& name);

private:
	irr::io::IrrXMLReaderUTF16* _reader;
};