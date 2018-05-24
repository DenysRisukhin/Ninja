#include "BadNinja.h"

BadNinja::BadNinja() : Enemy({ 0, 0, 0 }, 0, smgr, NULL) {}

BadNinja::~BadNinja(void) {}

double BadNinja::Distance(double dX0, double dY0, double dX1, double dY1) {
	return sqrt((dX1 - dX0)*(dX1 - dX0) + (dY1 - dY0)*(dY1 - dY0));
}

void BadNinja::faceTarget(irr::core::vector3df targetPos) {

	core::vector3df myRotation = this->node->getRotation();
	core::vector3df nodePos = targetPos - this->node->getPosition();
	myRotation.Y = atan(nodePos.Z / nodePos.X) * (180.0f / 3.14f); // irr::core::PI

	myRotation.Y -= 90;

	if ((targetPos.X - this->node->getPosition().X) > 0) {
		myRotation.Y = 90 - myRotation.Y;
	}
	else if ((targetPos.X - this->node->getPosition().X) < 0) {
		myRotation.Y = -90 - myRotation.Y;
	}

	myRotation.Y -= 90;
	this->node->setRotation(myRotation);
}

//IAnimatedMeshSceneNode* Enemy::getNode() {
//	return node;
//}

BadNinja::BadNinja(vector3df CoinsPosition, f32 newSpeed, scene::ISceneManager *smgr, Player* target, gui::IGUIStaticText *text, gui::IGUIEnvironment* env, video::IVideoDriver* driver)
	: Enemy(CoinsPosition, newSpeed, smgr, target) {

	this->smgr = smgr;
	this->text = text;
	//this->engine = engine;
	this->env = env;
	this->driver = driver;

	scene::IAnimatedMesh* building_mesh = this->smgr->getMesh("Models/ninja.b3d");
	this->node = this->smgr->addAnimatedMeshSceneNode(building_mesh);
	if (building_mesh == NULL) {
		printf("Nu putem incarca mesh-ul de player\n");
		exit(-1);
	}

	this->node->setMaterialTexture(0, driver->getTexture("Models/nskinrd.jpg"));
	this->node->setScale(core::vector3df(6, 6, 6));
	this->node->setRotation(core::vector3df(0, 260, 0));
	this->node->setPosition(core::vector3df(2000 * 2, -15, 2600 * 2));
	this->node->setMaterialFlag(video::EMF_LIGHTING, false);
	//this->node->setAnimationSpeed(30);
	this->node->setFrameLoop(1, 13);
	this->node->setAnimationSpeed(14);
	this->node->setMD2Animation("walk");


	//this->coin = new Coin(this->smgr, this->text, this->env, this->driver);

	/* Aici setez obiectul sa se miste in jurul monezii */
	scene::ISceneNodeAnimator* anim = smgr->createFlyCircleAnimator(CoinsPosition, 90, 0.001f);
	node->addAnimator(anim);
	anim->drop();
}

void BadNinja::update(f32 deltaTime) {
	//target->getNode();// ->updateAbsolutePosition();
	node->updateAbsolutePosition();
	move(target);
	/*coin->move();
	coin->coliziune(target);*/
}

void BadNinja::move(Player *player) {

	double d = Distance(player->getPosition().X, player->getPosition().Z, this->node->getPosition().X, this->node->getPosition().Z);

	// collision
	if (d < 100) {
		this->node->setFrameLoop(134, 145);
		this->node->setAnimationSpeed(14);
		this->node->setMD2Animation("SpinningSwordattack");
	}
	if (d < 15) {

		if (player->getHealth() == 0)
			return;

		player->takeDamage(1);// life--;

		/*std::string scor = "Coins: ";
		scor += std::to_string(player->score);
		std::wstring widestr = std::wstring(scor.begin(), scor.end());
		const wchar_t* widecstr = widestr.c_str();
		this->text->setText(widecstr);*/

		//player->dead = true;

		int iSecret = rand() % 10 + 1;
		player->setPosition(core::vector3df(2600 * 2.0f, 30 * 2.0f, 200 * 2.0f*iSecret));
		//player->setRotation(core::vector3df(0.0f, 180, 0.0f));
		player->camera->getNode()->updateAbsolutePosition();
	
	//	auto temp = node->getAbsolutePosition() - (player->camera->getNode()->getAbsolutePosition());
	//	auto cameraDistance = fabs(temp.getLength());
		
	//	player->camera->getNode()->setPosition(temp);

		//core::vector3df des_pos = player->getPosition();
		//des_pos += player->get_axis(0) * 0 + player->get_axis(1) * 10 + player->get_axis(2) * 15;
		//des_pos.Y = 300;
		//player->camera->setPosition(des_pos);

	}
	else if (d < 350) { // 650

		/*this->node->setFrameLoop(1, 13);
		this->node->setAnimationSpeed(14);
		this->node->setMD2Animation("walk");*/

		node->removeAnimators();
		core::vector3df dif = player->getPosition() - this->node->getPosition();
		dif = dif / 25; // 100
		this->node->setPosition(this->node->getPosition() + dif);
		faceTarget(player->getPosition());
	}
	/*else if (!this->coin->dead) {
		core::vector3df dif = (this->coin->node->getPosition() - this->node->getPosition());
		dif = dif / 200;
		this->node->setPosition(this->node->getPosition() + dif);
		faceTarget(this->coin->node->getPosition());
	}

	if (this->coin->dead) {
		node->removeAnimators();
		core::vector3df dif = player->getPosition() - this->node->getPosition();
		dif = dif / 100;
		this->node->setPosition(this->node->getPosition() + dif);
		faceTarget(player->getPosition());
	}*/

}

void BadNinja::move_around_coin() {}