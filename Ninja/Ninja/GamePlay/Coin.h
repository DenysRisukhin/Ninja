#pragma once

//#include "irrlicht\irrlicht.h"
//#include "irrKlang\irrKlang.h"
//#include "irrlicht\driverChoice.h"
#include <iostream>
#include <string>
#include "Player.h"
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include "Enemy.h"

using namespace irr;
//using namespace irrklang;


class Coin: public GameObject {

public:
	//Coin(void);
	~Coin(void);
	Coin(scene::ISceneManager*, gui::IGUIStaticText *, gui::IGUIEnvironment*, video::IVideoDriver*, vector3df);
	void move();
	//void coliziune(Player*);

	
	void update(f32 deltaTime);
	bool isNear(vector3df position);

	virtual void attack() {}
	virtual void dodge(f32 deltaTime) {} // увернуться
	virtual void run(f32 deltaTime) {}
	void remove();
private:
	double Distance(double, double, double, double);
private:
	scene::ISceneManager* smgr;
	gui::IGUIStaticText *text;
	//ISoundEngine* engine;
	video::IVideoDriver* driver;
	gui::IGUIEnvironment* env;
	//gui::IGUIImage *imag;
	int contor;
public:
	//scene::IAnimatedMeshSceneNode* node;
	IMeshSceneNode* node;
	//bool dead;
};

