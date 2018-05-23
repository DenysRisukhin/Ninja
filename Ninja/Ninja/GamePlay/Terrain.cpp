#include "Terrain.h"

Terrain::Terrain(ISceneManager* smgr, IVideoDriver* driver)
{
	//terrain = smgr->addTerrainSceneNode("Textures/terrain-heightmap.bmp");
	//terrain->setPosition(vector3df(0, 0, 0));
	//terrain->setScale(vector3df(40, 0.5, 40));
	//terrain->setMaterialFlag(EMF_LIGHTING, false);
	//terrain->setMaterialTexture(0, driver->getTexture("Textures/terrain-texture.bmp"));

	// add terrain scene node
	this->terrain = smgr->addTerrainSceneNode(
		"Textures/light.bmp",
		0,									// parent 
		-1,									// node id
		core::vector3df(0.f, 0.f, 0.f),		// position
		core::vector3df(0.f, 0.f, 0.f),		// rotation
		core::vector3df(40.f, 4.4f, 40.f),	// scale
		video::SColor(255, 255, 255, 255),// vertexColor
		5,									// maxLOD
		scene::ETPS_17,						// patchSize
		4									// smoothFactor
	);

	this->terrain->setMaterialFlag(video::EMF_LIGHTING, false);
	this->terrain->setMaterialTexture(0, driver->getTexture("Textures/terrain-texture.jpg"));
	this->terrain->setMaterialTexture(1, driver->getTexture("Textures/detailmap3.jpg"));
	this->terrain->setMaterialType(video::EMT_DETAIL_MAP);
	this->terrain->scaleTexture(1.0f, 20.0f);
}

ITerrainSceneNode* Terrain::getNode()
{
	return terrain;
}