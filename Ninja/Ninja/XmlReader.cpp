#include "XmlReader.h"
#include "InitException.h"

using namespace irr;
using namespace core;
using namespace io;

XmlReader::XmlReader(const char* filename)
		 : _reader(createIrrXMLReaderUTF16(filename))

{
	if (!_reader)
		throw InitException("_reader");
}

XmlReader::~XmlReader(void)
{
	delete _reader;
}

bool XmlReader::next()
{
	if (!_reader)
		return false;

	bool result;
	while ((result = _reader->read()) && _reader->getNodeType() == EXN_ELEMENT_END);

	if (!result) {
		delete _reader;
		_reader = 0;
	}

	return result;
}

stringw XmlReader::getNodeName()
{
	return stringw(_reader->getNodeName());
}

stringw XmlReader::getAttributeValue(const stringw& name)
{
	return stringw(_reader->getAttributeValue((const char16*)name.c_str()));
}

int XmlReader::getAttributeValueAsInt(const stringw& name)
{
	return _reader->getAttributeValueAsInt((const char16*)name.c_str());
}

float XmlReader::getAttributeValueAsFloat(const stringw& name)
{
	return _reader->getAttributeValueAsFloat((const char16*)name.c_str());
}