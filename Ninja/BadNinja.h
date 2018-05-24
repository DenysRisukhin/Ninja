#pragma once

#include "Coin.h"
#include "Player.h"
#include "Enemy.h"

using namespace irr;
//using namespace irrklang;

class BadNinja : public Enemy {
public:
	BadNinja();
	~BadNinja(void);
	BadNinja(vector3df position, f32 newSpeed, scene::ISceneManager*, Player* target, gui::IGUIStaticText *, gui::IGUIEnvironment*, video::IVideoDriver*);
	void move(Player *);
	void move_around_coin();

	virtual void update(f32 deltaTime);

	virtual void attack() {}
	virtual void dodge(f32 deltaTime) {} // увернуться
	virtual void run(f32 deltaTime) {}

	//IAnimatedMeshSceneNode* getNode();
private:
	void faceTarget(irr::core::vector3df);
	double Distance(double, double, double, double);
private:
	scene::ISceneManager* smgr;
	gui::IGUIStaticText *text;
	//ISoundEngine* engine;
	video::IVideoDriver* driver;
	gui::IGUIEnvironment* env;
public:
	//scene::IAnimatedMeshSceneNode* node;
	//Coin *coin;
};
