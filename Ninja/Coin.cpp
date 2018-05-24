#include "Coin.h"

//Coin::Coin(void) {}
Coin::~Coin(void) {}

double Coin::Distance(double dX0, double dY0, double dX1, double dY1) {
	return sqrt((dX1 - dX0)*(dX1 - dX0) + (dY1 - dY0)*(dY1 - dY0));
}

Coin::Coin(scene::ISceneManager *smgr, gui::IGUIStaticText *text, gui::IGUIEnvironment* env, video::IVideoDriver* videoDriver, vector3df pos): driver(videoDriver), GameObject(pos, 0, smgr)
{
	this->smgr = smgr;
	this->text = text;
	//this->engine = engine;
	this->env = env;
	this->driver = driver;

	this->contor = 120;

	/*scene::IAnimatedMesh* building_mesh = this->smgr->getMesh("Models/coin.obj");
	this->node = this->smgr->addAnimatedMeshSceneNode(building_mesh);
	if (building_mesh == NULL) {
		printf("Nu putem incarca mesh-ul de player\n");
		exit(-1);
	}*/

	scene::IMesh* building_mesh = this->smgr->getMesh("Models/coin.obj");
	this->node = this->smgr->addMeshSceneNode(building_mesh);

	if (building_mesh == NULL) {
		printf("Nu putem incarca mesh-ul de player\n");
		exit(-1);
	}

	//node = smgr->addCubeSceneNode(20.0f, NULL, -1, vector3df(origPosition));
	//node->setMaterialFlag(EMF_LIGHTING, false);
	////node->setScale(vector3df(45, 45, 45));

	//node->setMaterialTexture(0, driver->getTexture("Textures/Cube.bmp"));

	this->node->setScale(core::vector3df(15, 15, 15));
	this->node->setPosition(pos);
	this->node->setMaterialFlag(video::EMF_LIGHTING, false);
	this->node->setRotation(core::vector3df(0, 0, 90));

	//this->dead = false;
}

void Coin::remove()
{
	node->remove();
}

//void Coin::coliziune(Player *player) {

	//if (this->dead) {

	//	this->contor--;

	//	if (this->contor == 0)
	//		//this->imag->setVisible(false);

	//	return;
	//}

	//double d = Distance(player->getPosition().X, player->getPosition().Z, this->node->getPosition().X, this->node->getPosition().Z);

	////std::cout << dif.X << " " << dif.Y << " " << dif.Z << std::endl;
	//if (d < 80) {

	////	this->imag = env->addImage(driver->getTexture("media/welldone.png"), core::position2d<int>(120, 120));

	////	this->engine->play2D("media/sounds/coin.wav", false);

	//	this->dead = true;
	//	this->smgr->addToDeletionQueue(this->node);
	////	std::string scor = "Coins: ";
	////	player->score++;
	////	scor += std::to_string(player->score);
	////	std::wstring widestr = std::wstring(scor.begin(), scor.end());
	////	const wchar_t* widecstr = widestr.c_str();
	////	text->setText(widecstr);
	//}

//}

void Coin::move() {

	/*if (this->dead)
		return;

	this->node->setRotation(this->node->getRotation() + core::vector3df(1, 0, 0));*/

}

bool Coin::isNear(vector3df position)
{
	if ((origPosition - position).getLengthSQ() < 2500)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//void Coin::remove()
//{
//	//if (node) {
//		node->remove();
////	}
//}

void Coin::update(f32 deltaTime)
{
	//if (this->dead)
	//	return;

//	if(node)
		node->setRotation(this->node->getRotation() + core::vector3df(1, 0, 0));
}