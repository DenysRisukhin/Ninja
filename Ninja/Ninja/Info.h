#pragma once

#include <irrlicht.h>
#include "IConfigReader.h"
#include "Game.h"
#include "InitException.h"
//#include "NotImplementedException.h"

using namespace irr;
using namespace core;
using namespace io;

/*!
Represents base class for any Info.
Derive any config class from it and implement OnNode.
Use family of template methods to obtain data.
*/
class Info 
{
public:
	/*!
	Creates config from file using Irrlicht's filesystem.
	*/
	Info(Game* game, const irr::io::path& filename);

	/*!
	Creates config using provided reader.
	*/
	Info(Game* game, IConfigReader* reader);

	/*!
	Frees allocated resources.
	*/
	~Info(void);

	Info() {}
	Info(Info &&) {}
	//Config(const Config&) = default;
	//Config& operator=(const Config&) = default;

protected:
	/*!
	Should be called to move to the next node.
	Returns false if no more nodes left.
	*/
	bool next();

	/*!
	Should be implemented by the descendants (потомки)
	to process values of attributes of the node. // для обработки значений атрибутов узла.
	*/
	virtual void OnNode(const stringw& name) = 0;

	template <class T> 
	T read(const stringw& attributeName)
	{
		throw NotImplementedException();
	}

	/*!
	Reads stringw from node's attribute with provided name.
	*/
	template <>
	stringw read<irr::core::stringw>(const stringw& attributeName)
	{
		stringw result = _reader->getAttributeValue(attributeName.c_str());
		if (!result.size())
			throw InitException(attributeName);
		return result;
	}

	/*!
	Reads bool from node's attribute with provided name.
	*/
	template <> 
	bool read<bool>(const stringw& attributeName)
	{
		stringw value = read<stringw>(attributeName);
		value.make_lower();
		return value == "true" || value == "1";
	}

	/*!
	Reads s32 from node's attribute with provided name.
	*/
	template <> 
	s32 read<s32>(const stringw& attributeName)
	{
		return (s32) _reader->getAttributeValueAsInt(attributeName.c_str());
	}

	/*!
	Reads u32 from node's attribute with provided name.
	Warning! Result is equivalent of "(u32) read<s32>"!
	*/
	template <> 
	u32 read<u32>(const stringw& attributeName)
	{
		return (u32) _reader->getAttributeValueAsInt(attributeName.c_str());
	}

	/*!
	Reads f32 from node's attribute with provided name.
	*/
	template <> 
	f32 read<f32>(const stringw& attributeName)
	{
		return (f32) _reader->getAttributeValueAsFloat(attributeName.c_str());
	}

	/*!
	Reads path from node's attribute with provided name.
	Path is checked to be correct.
	*/
	template <> 
	path read<path>(const stringw& attributeName)
	{
		stringw result = read<stringw>(attributeName);
		if (!_game->getDevice()->getFileSystem()->existFile(result))
			throw InitException(attributeName);
		return result;
	}

	/*!
	Reads ITexture from node's attribute with provided name.
	(Considers node's attribure value as path to the texture file.)
	*/
	template <> 
	ITexture* read<ITexture*>(const stringw& attributeName)
	{
		ITexture* result =_game->getDevice()->getVideoDriver()->getTexture(read<path>(attributeName));
		if (!result)
			throw InitException(attributeName);
		return result;
	}

	/*!
	Reads IGUIFont from node's attribute with provided name.
	(Considers node's attribure value as path to the font file.)
	*/
	template <>
	IGUIFont* read<IGUIFont*>(const stringw& attributeName)
	{
		IGUIFont* result = _game->getDevice()->getGUIEnvironment()->getFont(read<path>(attributeName));
		if (!result)
			throw InitException(attributeName);
		return result;
	}

	/*!
	Reads SColor from node's attribute with provided name.
	*/
	template <> 
	SColor read<SColor>(const stringw& attributeName)
	{
		SColor color(0xFF000000);

		color.setRed(read<irr::u32>(attributeName + "Red"));
		color.setGreen(read<irr::u32>(attributeName + "Green"));
		color.setBlue(read<irr::u32>(attributeName + "Blue"));

		return color;
	}

	/*!
	Reads IAnimatedMesh from node's attribute with provided name.
	(Considers node's attribure value as path to the mesh file.)
	*/
	template <> 
	IAnimatedMesh* read<IAnimatedMesh*>(const stringw& attributeName)
	{
		IAnimatedMesh* result = _game->getDevice()->getSceneManager()->getMesh(read<path>(attributeName));
		if (!result)
			throw InitException(attributeName);
		return result;
	}

	Game* _game;

private:
	IConfigReader* _reader;
};
