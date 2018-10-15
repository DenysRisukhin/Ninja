#include "Game.h"

Game::Game()
{
	updateList = list<GameObject*>();
	listCoin = list<Coin*>();
	lastUpdate = 0.0f;
	timeSinceStart = 0.0f;
	selector = NULL;
	delayTimer = 0;
	pickup_0 = NULL;
	pickup_1 = NULL;

	gamePaused = false;
	bMainMenuDisplayed = false;
	bGameOverDisplayed = false;
	bGameCompleteDisplayed = false;
	numOfEnemies = 0;

	bWave0Finished = false;
	bWave1Finished = false;
	bWave2Finished = false;
	bWave3Finished = false;
	bWave4Finished = false;
	bWave5Finished = false;

	bWave0Started = false;
	bWave1Started = false;
	bWave2Started = false;
	bWave3Started = false;
	bWave4Started = false;
	bWave5Started = false;
}

f32 Game::getLastUpdate()
{
	return lastUpdate;
}

void Game::setLastUpdate(f32 update)
{
	lastUpdate = update;
}

u8 Game::getNumOfEnemies()
{
	return numOfEnemies;
}

// Function to handle user input.
void Game::processInput(IrrlichtDevice* device, ISceneManager* smgr, IVideoDriver* driver, ITriangleSelector* selector, EventReciever* reciever, Player* player, Camera* camera, f32 deltaTime, ISoundEngine* sound)
{
	bool pPressed = false;

	if (reciever->isKeyDown(KEY_KEY_W))
	{
		player->moveForward(deltaTime);

		if (!reciever->isKeyDown(KEY_SPACE))
			player->setRunningAnimation();
	}
	if (reciever->isKeyDown(KEY_KEY_S))
	{
		player->moveBackward(deltaTime);

		if (!reciever->isKeyDown(KEY_SPACE))
			player->setRunningAnimation();
	}
	if (reciever->isKeyDown(KEY_KEY_A))
	{
		player->turnLeft(deltaTime);
	}
	if (reciever->isKeyDown(KEY_KEY_D))
	{
		player->turnRight(deltaTime);
	}
	if (reciever->isKeyDown(KEY_KEY_Q))
	{
		player->strafeRight(deltaTime);
		player->setRunningAnimation();
	}
	if (reciever->isKeyDown(KEY_KEY_E))
	{
		player->strafeLeft(deltaTime);
		player->setRunningAnimation();
	}
	if (reciever->isKeyDown(KEY_KEY_Z))
	{
		PowerBall* tempBall = player->Attack();
		if (tempBall != NULL)
		{
			sound->play2D("sounds/lazer.wav", false);
			updateList.push_back(tempBall);
		}
		player->setAttackAnimation();
	}
	/*if (reciever->isKeyDown(KEY_KEY_X))
	{
		pushEnemies(player);
		player->setAttackAnimation();
	}
	if (reciever->isKeyDown(KEY_KEY_C))
	{
		player->teleport();
	}*/

	if (reciever->isKeyDown(KEY_SPACE)) {

		player->setJumpAnimation();
		
	}

	if (reciever->isKeyUp(KEY_KEY_X) && reciever->isKeyUp(KEY_KEY_Z) && reciever->isKeyUp(KEY_KEY_W) && reciever->isKeyUp(KEY_KEY_A) && reciever->isKeyUp(KEY_KEY_S) && reciever->isKeyUp(KEY_KEY_D) && !reciever->isKeyDown(KEY_SPACE))
	{
		player->setIdleAnimation();
	}

}

// Function to update position of all GameObjects.
void Game::updateGameObjects(f32 deltaTime)
{
	if (updateList.getSize() != 0)
	{
		list<GameObject*>::Iterator it = list<GameObject*>::Iterator();
		it = updateList.begin();
		for (int i = 0; i < updateList.getSize(); i++)
		{
			GameObject* ptr = NULL;
			list<GameObject*>::Iterator tempIterator = list<GameObject*>::Iterator();
			if (updateList.getSize() == 0)
			{
				return;
			}
			if (it.operator!=(tempIterator))
			{
				ptr = it.operator*();
			}

			if (ptr != NULL)
			{
				if (!ptr->needsUpdate())
				{
					ptr->kill();
					ptr->getNode()->remove();
					updateList.erase(it);
				}
				else
				{
					ptr->update(deltaTime);
					it.operator++();
				}
			}
		}
	}
}

// Handle all the collisions.
void Game::handleCollisions(Player* player, Camera* camera, f32 deltaTime)
{
	handleCollisionWithPlayer(player, camera, deltaTime);
	handleCollisionEnemyPowerBall();
}

// Handle collisions between Enemies and PowerBalls.
void Game::handleCollisionEnemyPowerBall(void)
{
	if (updateList.getSize() != 0)
	{
		GameObject* ptr = NULL;

		list<GameObject*>::Iterator it = list<GameObject*>::Iterator();
		list<GameObject*>::Iterator tempIterator = list<GameObject*>::Iterator();
		it = updateList.begin();

		// Going through all GameObjects.
		for (int i = 0; i < updateList.getSize(); ++i)
		{
			// Check for it.current = NULL.
			if (it.operator==(tempIterator))
			{
				return;
			}

			// Check for Enemy.
			ptr = dynamic_cast<Enemy*>(it.operator*());
			if (ptr != NULL)
			{
				// Enemy instance.
				if (collisionsBetweenEnemyAndBalls(ptr->getNode()))
				{
					// Removing enemy from updateList.
					--numOfEnemies;
					updateList.erase(it);
					continue;
				}

				handleCollisionBetweenEnemies(ptr);
			}

			// Check for it.current->next = NULL.
			if (tempIterator.operator==(it.operator++()))
			{
				return;
			}
		}
	}
}

// Handle collision of GameObjects with the player.
void Game::handleCollisionWithPlayer(Player* player, Camera* camera, f32 deltaTime)
{
	// First check for collisions with Pickups.
	if (pickup_0 != NULL)
	{
		if (pickup_0->isNear(player->getPosition()))
		{
			player->takePickup();
			pickup_0->remove();
			pickup_0 = NULL;
		}
	}
	if (pickup_1 != NULL)
	{
		if (pickup_1->isNear(player->getPosition()))
		{
			player->takePickup();
			pickup_1->remove();
			pickup_1 = NULL;
		}
	}

	
	//----------------COINS 
	if (listCoin.getSize() != 0)
	{
		Coin* ptr = NULL;

		list<Coin*>::Iterator it = list<Coin*>::Iterator();
		list<Coin*>::Iterator tempIterator = list<Coin*>::Iterator();
		it = listCoin.begin();

		// Going through all GameObjects.
		for (int i = 0; i < listCoin.getSize(); ++i)
		{
			// Check for it.current = NULL.
			if (it.operator==(tempIterator))
			{
				return;
			}

			// Check for Coin.
			ptr = dynamic_cast<Coin*>(it.operator*());
			if (ptr != NULL)
			{
				if (ptr->isNear(player->getPosition()))
				{
				
					// coin labelCounter++
					auto temp = it;

					ptr->remove();
					ptr = NULL;

					listCoin.erase(temp);

					std::cout << "Coin removed.\n";
				}
				else {
					ptr->update(deltaTime);
				}
			}

			// Check for it.current->next = NULL.
			if (tempIterator.operator==(it.operator++()))
			{
				
				return;
			}
		}
	}

	// Now for the other GameObjects.
	if (updateList.getSize() != 0)
	{
		GameObject* ptr = NULL;

		list<GameObject*>::Iterator it = list<GameObject*>::Iterator();
		list<GameObject*>::Iterator tempIterator = list<GameObject*>::Iterator();
		it = updateList.begin();

		// Going through all the GameObjects.
		for (int i = 0; i < updateList.getSize(); ++i)
		{
			// Check for it.current = NULL.
			if (it.operator==(tempIterator))
			{
				return;
			}

			// Check for PowerBallEnemy.
			ptr = dynamic_cast<PowerBallEnemy*>(it.operator*());
			if (ptr != NULL)
			{
				// PowerBallEnemy instance.

				const aabbox3df boxForPowerBallEnemy = ptr->getNode()->getTransformedBoundingBox();
				const aabbox3df boxForPlayer = player->getNode()->getTransformedBoundingBox();

				if (boxForPowerBallEnemy.intersectsWithBox(boxForPlayer))
				{
					ptr->getNode()->remove();
					updateList.erase(it);
					player->takeDamage(POWER_BALL);
					//std::cout << "Collision between player and ball.\n";
				}

				// Check for it.current = NULL.
				if (tempIterator.operator==(it))
				{
					return;
				}

				// Check for it.current->next = NULL.
				if (tempIterator.operator==(it.operator++()))
				{
					return;
				}

				continue;
			}

			// Check for PowerBall.
			ptr = dynamic_cast<PowerBall*>(it.operator*());
			if (ptr != NULL)
			{
				// PowerBall instance.
				// No collision required.

				// Check for it.current = NULL.
				if (tempIterator.operator==(it))
				{
					return;
				}

				// Check for it.current->next = NULL.
				if (tempIterator.operator==(it.operator++()))
				{
					return;
				}

				continue;
			}

			// Check for BadNinja.
			ptr = dynamic_cast<BadNinja*>(it.operator*());
			if (ptr != NULL)
			{
				// BadNinja instance.
				const aabbox3df boxForBadNinja = ptr->getNode()->getTransformedBoundingBox();
				const aabbox3df boxForPlayer = player->getNode()->getTransformedBoundingBox();

				if (boxForBadNinja.intersectsWithBox(boxForPlayer))
				{
					player->moveBackward(deltaTime);
				}

				// Check for it.current = NULL.
				if (tempIterator.operator==(it))
				{
					return;
				}

				// Check for it.current->next = NULL.
				if (tempIterator.operator==(it.operator++()))
				{
					return;
				}

				continue;
			}

			// Check for BadFaerie.
			ptr = dynamic_cast<BadFaerie*>(it.operator*());
			if (ptr != NULL)
			{
				// BadFaerie instance.
				const aabbox3df boxForFaerie = ptr->getNode()->getTransformedBoundingBox();
				const aabbox3df boxForPlayer = player->getNode()->getTransformedBoundingBox();

				if (boxForFaerie.intersectsWithBox(boxForPlayer))
				{
					player->moveBackward(deltaTime);
				}

				// Check for it.current = NULL.
				if (tempIterator.operator==(it))
				{
					return;
				}

				// Check for it.current->next = NULL.
				if (tempIterator.operator==(it.operator++()))
				{
					return;
				}

				continue;
			}

			// Check for Monster.
			ptr = dynamic_cast<Monster*>(it.operator*());
			if (ptr != NULL)
			{
				// Monster instance.
				const aabbox3df boxForMonster = ptr->getNode()->getTransformedBoundingBox();
				const aabbox3df boxForPlayer = player->getNode()->getTransformedBoundingBox();

				if (boxForMonster.intersectsWithBox(boxForPlayer))
				{
					player->moveBackward(deltaTime);
				}

				// Check for it.current = NULL.
				if (tempIterator.operator==(it))
				{
					return;
				}

				// Check for it.current->next = NULL.
				if (tempIterator.operator==(it.operator++()))
				{
					return;
				}

				continue;
			}

			// Check for Wraith.
			ptr = dynamic_cast<Wraith*>(it.operator*());
			if (ptr != NULL)
			{
				// Wraith instance.
				const aabbox3df boxForWraith = ptr->getNode()->getTransformedBoundingBox();
				const aabbox3df boxForPlayer = player->getNode()->getTransformedBoundingBox();

				if (boxForWraith.intersectsWithBox(boxForPlayer))
				{
					player->moveBackward(deltaTime);
				}

				// Check for it.current = NULL.
				if (tempIterator.operator==(it))
				{
					return;
				}

				// Check for it.current->next = NULL.
				if (tempIterator.operator==(it.operator++()))
				{
					return;
				}

				continue;
			}


		}
	}
}

// Function to handle collisions between Enemy and Powerball.
bool Game::collisionsBetweenEnemyAndBalls(ISceneNode* enemy)
{
	if (updateList.getSize() != 0)
	{
		GameObject* ptr1 = NULL, *ptr2 = NULL;

		list<GameObject*>::Iterator it = list<GameObject*>::Iterator();
		list<GameObject*>::Iterator tempIterator = list<GameObject*>::Iterator();
		it = updateList.begin();

		// Going through all GameObjects to detect PowerBalls.
		for (int i = 0; i < updateList.getSize(); ++i)
		{
			// Check for it.current = NULL.
			if (it.operator==(tempIterator))
			{
				return false;
			}

			ptr1 = dynamic_cast<PowerBall*>(it.operator*());
			ptr2 = dynamic_cast<PowerBallEnemy*>(it.operator*());

			// Check for PowerBall.
			if (ptr1 != NULL && ptr2 == NULL)
			{
				// PowerBall instance.
				if (ptr1->getNode() == NULL)
				{
					it.operator++();
					continue;
				}

				aabbox3df boxForBall = ptr1->getNode()->getTransformedBoundingBox();
				aabbox3df boxForEnemy = enemy->getTransformedBoundingBox();

				if (boxForBall.intersectsWithBox(boxForEnemy))
				{
					//std::cout << "Collision occurred.\n";
					// Removing enemy from the scene.
					enemy->remove();

					// Removing PowerBall from scene and updateList.
					ptr1->getNode()->remove();
					updateList.erase(it);

					// Return value to remove enemy from updateList.
					return true;
				}

			}
			else
			{
				// Not a PowerBall instance.
			}

			// Check for it.current = NULL.
			if (tempIterator.operator==(it))
			{
				return false;
			}

			// Check for it.current->next = NULL.
			if (tempIterator.operator==(it.operator++()))
			{
				return false;
			}
		}
	}
	return false;
}

// Function to handle collisions between faerie and player.
void Game::collisionBetweenFaerieAndPlayer(Player* player, Camera* camera, ISceneNode* faerie, f32 deltaTime)
{
	if (updateList.getSize() != 0)
	{
		aabbox3df boxForPlayer = player->getNode()->getTransformedBoundingBox();
		aabbox3df boxForFaerie = faerie->getTransformedBoundingBox();

		if (boxForPlayer.intersectsWithBox(boxForFaerie))
		{
			player->getNode()->updateAbsolutePosition();
			faerie->updateAbsolutePosition();
			player->moveBackward(deltaTime);
		}
	}
}

// Function to handle collision between two enemies.
void Game::handleCollisionBetweenEnemies(GameObject* enemy)
{
	Enemy* firstEnemy = dynamic_cast<Enemy*>(enemy);

	if (firstEnemy == NULL)
	{
		return;
	}

	if (updateList.getSize() != 0)
	{
		GameObject* ptr = NULL;

		list<GameObject*>::Iterator it = list<GameObject*>::Iterator();
		list<GameObject*>::Iterator tempIterator = list<GameObject*>::Iterator();
		it = updateList.begin();

		// Going through all GameObjects.
		for (int i = 0; i < updateList.getSize(); ++i)
		{
			// Check for it.current = NULL.
			if (it.operator==(tempIterator))
			{
				return;
			}

			// Check for Enemy.
			ptr = dynamic_cast<Enemy*>(it.operator*());
			if (ptr != NULL)
			{
				// Enemy instance.
				Enemy* secondEnemy = dynamic_cast<Enemy*>(ptr);

				const aabbox3df boxForFirst = firstEnemy->getNode()->getTransformedBoundingBox();
				const aabbox3df boxForSecond = secondEnemy->getNode()->getTransformedBoundingBox();

				if (boxForFirst.intersectsWithBox(boxForSecond))
				{
					vector3df direction = firstEnemy->getPosition() - secondEnemy->getPosition();
					direction.normalize();

					firstEnemy->getNode()->setPosition(firstEnemy->getPosition() + (direction * firstEnemy->getSpeed()));
					secondEnemy->getNode()->setPosition(secondEnemy->getPosition() + (-1.0f * direction * secondEnemy->getSpeed()));
				}
			}

			// Check for it.current->next = NULL.
			if (tempIterator.operator==(it.operator++()))
			{
				return;
			}
		}
	}
}

// Function to handle Game State.
void Game::handleGameState(GameState & gameState, Player* player, IrrlichtDevice* irrDevice, ISceneManager* smgr, IVideoDriver* driver)
{
	switch (gameState)
	{
	case MAIN_MENU:
		if (!bMainMenuDisplayed)
		{
			displayMainMenu(gameState, irrDevice);
			bMainMenuDisplayed = true;
		}
		bGameCompleteDisplayed = false;
		bGameOverDisplayed = false;
		break;

	case WAVE_0:
		if (player->getPosition().Y < 0)
		{
			player->kill();
		}
		if (player->isDead())
		{
			gameState = GAME_OVER;
		}
		else if (bWave0Finished)
		{
			gameState = WAVE_1;
		}
		else if (!bWave0Started && updateList.getSize() == 0)
		{
			bMainMenuDisplayed = false;
			initiateWave0(player, irrDevice, smgr, driver);
			std::cout << "Wave 0 started.\n";
		}
		else
		{
			updateWaveStatus(gameState, irrDevice, player, smgr, driver);
		}
		break;

	case WAVE_1:
		if (player->getPosition().Y < 0)
		{
			player->kill();
		}
		if (player->isDead())
		{
			gameState = GAME_OVER;
		}
		else if (bWave1Finished)
		{
			gameState = WAVE_2;
		}
		else if (!bWave1Started && updateList.getSize() == 0)
		{
			bMainMenuDisplayed = false;
			initiateWave1(player, irrDevice, smgr, driver);
			std::cout << "Wave 1 started.\n";
		}
		else
		{
			updateWaveStatus(gameState, irrDevice, player, smgr, driver);
		}
		break;

	case WAVE_2:
		if (player->getPosition().Y < 0)
		{
			player->kill();
		}
		if (player->isDead())
		{
			gameState = GAME_OVER;
		}
		if (bWave2Finished)
		{
			gameState = WAVE_3;
		}
		else if (!bWave2Started && updateList.getSize() == 0)
		{
			initiateWave2(player, irrDevice, smgr, driver);
			std::cout << "Wave 2 started.\n";
		}
		else
		{
			updateWaveStatus(gameState, irrDevice, player, smgr, driver);
		}
		break;

	case WAVE_3:
		if (player->getPosition().Y < 0)
		{
			player->kill();
		}
		if (player->isDead())
		{
			gameState = GAME_OVER;
		}
		if (bWave3Finished)
		{
			gameState = GAME_COMPLETE;
		}
		else if (!bWave3Started && updateList.getSize() == 0)
		{
			initiateWave3(player, irrDevice, smgr, driver);
			std::cout << "Wave 3 started.\n";
		}
		else
		{
			updateWaveStatus(gameState, irrDevice, player, smgr, driver);
		}
		break;

	case GAME_COMPLETE:
		if (!bGameCompleteDisplayed)
		{
			displayGameCompleteScreen(driver, irrDevice->getGUIEnvironment());
			bGameCompleteDisplayed = true;
			delayTimer = irrDevice->getTimer()->getTime();
		}
		else
		{
			// Delay for 5 seconds.
			if ((irrDevice->getTimer()->getTime() - delayTimer) > 5000)
			{
				irrDevice->closeDevice();
			}
		}
		break;

	case GAME_OVER:
		if (!bGameOverDisplayed)
		{
			displayGameOverScreen(driver, irrDevice->getGUIEnvironment());
			bGameOverDisplayed = true;
			delayTimer = irrDevice->getTimer()->getTime();
		}
		else
		{
			// Delay for 5 seconds.
			if ((irrDevice->getTimer()->getTime() - delayTimer) > 5000)
			{
				irrDevice->closeDevice();
			}
		}
		break;

	default:
		break;
	}
}

// Function to denote that Game is Over.
void Game::displayGameOverScreen(IVideoDriver* driver, IGUIEnvironment* guienv)
{
	guienv->addImage(driver->getTexture("Textures/GameOver.jpg"), vector2d<s32>(-195, 0), false);
	bGameOverDisplayed = true;
}

// Function to denote completion of game.
void Game::displayGameCompleteScreen(IVideoDriver* driver, IGUIEnvironment* guienv)
{
	guienv->addImage(driver->getTexture("Textures/GameComplete.jpg"), vector2d<s32>(-195, 0), false);
	bGameCompleteDisplayed = true;
}

// Function to start Wave 0.
void Game::initiateWave0(Player* player, IrrlichtDevice* device, ISceneManager* smgr, IVideoDriver* driver)
{
	bWave0Started = true;

	/*for (int i = 0; i < 3; ++i)
	{
		spawnMonster(player, device, smgr, driver);

		spawnBadFaerie(player, device, smgr, driver);
	}

	spawnWraith(player, device, smgr, driver);*/

	timeSinceStart = device->getTimer()->getTime();
}

// Function to start Wave 1.
void Game::initiateWave1(Player* player, IrrlichtDevice* device, ISceneManager* smgr, IVideoDriver* driver)
{
	bWave1Started = true;

	// Spawn Monster.
	for (int i = 0; i < 3; ++i)
	{
		spawnMonster(player, device, smgr, driver);
	}

	timeSinceStart = device->getTimer()->getTime();
}

// Function to start Wave 2.
void Game::initiateWave2(Player* player, IrrlichtDevice* device, ISceneManager* smgr, IVideoDriver* driver)
{
	bWave2Started = true;

	for (int i = 0; i < 3; ++i)
	{
		spawnBadFaerie(player, device, smgr, driver);
	}

	timeSinceStart = device->getTimer()->getTime();
}

// Function to start Wave 3.
void Game::initiateWave3(Player* player, IrrlichtDevice* device, ISceneManager* smgr, IVideoDriver* driver)
{
	bWave3Started = true;

	pickup_0 = new HealthPickup(vector3df(200, 50, 200), 0, smgr, driver);
	spawnWraith(player, device, smgr, driver);

	timeSinceStart = device->getTimer()->getTime();
}

// Function to start Wave 4.
void Game::initiateWave4(Player* player, IrrlichtDevice* device, ISceneManager* smgr, IVideoDriver* driver)
{
	bWave4Started = true;

	for (int i = 0; i < 3; ++i)
	{
		spawnMonster(player, device, smgr, driver);
	}
	for (int i = 0; i < 2; ++i)
	{
		spawnBadFaerie(player, device, smgr, driver);
	}

	timeSinceStart = device->getTimer()->getTime();
}

// Function to start Wave 5.
void Game::initiateWave5(Player* player, IrrlichtDevice* device, ISceneManager* smgr, IVideoDriver* driver)
{
	bWave5Started = true;

	for (int i = 0; i < 3; ++i)
	{
		spawnMonster(player, device, smgr, driver);
	}
	for (int i = 0; i < 3; ++i)
	{
		spawnBadFaerie(player, device, smgr, driver);
	}
	spawnWraith(player, device, smgr, driver);

	timeSinceStart = device->getTimer()->getTime();
}

// Function to determine if wave is finished or player is dead.
void Game::updateWaveStatus(GameState & gameState, IrrlichtDevice* device, Player* player, ISceneManager* smgr, IVideoDriver* driver)
{
	// Check if updateList has any Enemy objects.
	bool bEnemyFound = false;

	switch (gameState)
	{
	case WAVE_0:
		if ((device->getTimer()->getTime() - timeSinceStart) > 0.0 && bWave0Started && !bWave0Finished)
		{
			for (int i = 0; i < 5; ++i)
			{
				auto coinPos = core::vector3df((1 + rand() % 10) * 550, 25, (1 + rand() % 15) * 500);

				auto _coin = new Coin(smgr, NULL, smgr->getGUIEnvironment(), driver, coinPos);
				listCoin.push_back(_coin);
				spawnBadNinja(player, device, smgr, driver, core::vector3df(coinPos.X, 5, coinPos.Z));
			}
			std::cout << "Wave 0 afterwave spawned.\n";
			bWave0Finished = true;
		}
		break;

	case WAVE_1:
		if ((device->getTimer()->getTime() - timeSinceStart) > 10000.0f && bWave1Started && !bWave1Finished)
		{
			for (int i = 0; i < 5; ++i)
			{
				spawnMonster(player, device, smgr, driver);
			}
			std::cout << "Wave 1 afterwave spawned.\n";
			bWave1Finished = true;
		}
		break;

	case WAVE_2:
		if ((device->getTimer()->getTime() - timeSinceStart) > 15000.0f && bWave2Started && !bWave2Finished)
		{
			for (int i = 0; i < 5; ++i)
			{
				spawnBadFaerie(player, device, smgr, driver);
			}
			std::cout << "Wave 2 afterwave spawned.\n";
			bWave2Finished = true;
		}
		break;

	case WAVE_3:
		if ((device->getTimer()->getTime() - timeSinceStart) > 20000.0f && bWave3Started && !bWave3Finished)
		{
			/*for (int i = 0; i < 3; ++i)
			{
				spawnWraith(player, device, smgr, driver);
			}*/
			std::cout << "Wave 3 afterwave spawned.\n";
			bWave3Finished = true;
		}
		break;

	default:
		break;
	}
}

// Function to push back enemies.
void Game::pushEnemies(Player* player)
{
	if (!player->push())
	{
		return;
	}

	if (updateList.getSize() != 0)
	{
		GameObject* ptr = NULL;

		list<GameObject*>::Iterator it = list<GameObject*>::Iterator();
		list<GameObject*>::Iterator tempIterator = list<GameObject*>::Iterator();
		it = updateList.begin();

		// Going through all the GameObjects.
		for (int i = 0; i < updateList.getSize(); ++i)
		{
			// Check for it.current = NULL.
			if (it.operator==(tempIterator))
			{
				return;
			}

			ptr = dynamic_cast<Enemy*>(it.operator*());
			if (ptr != NULL)
			{
				ptr->pushBack();
			}

			if (tempIterator.operator==(it.operator++()))
			{
				return;
			}
		}
	}
}

// Function to spawn BadNinja instance.
void Game::spawnBadNinja(Player* player, IrrlichtDevice* device, ISceneManager* smgr, IVideoDriver* driver, vector3df coinPos) {
	++numOfEnemies;
	bool bMatched;

	gui::IGUIStaticText *text = device->getGUIEnvironment()->addStaticText(L"Coins: 0", core::rect<s32>(10, 400, 150, 420), true, true, 0, -1, true);
		
	BadNinja *redNinja = new BadNinja(coinPos, 0.1f, smgr, player, text, device->getGUIEnvironment(), driver);

	const aabbox3df & box2 = redNinja->getNode()->getBoundingBox();
	vector3df radius = box2.MaxEdge - box2.getCenter();
	redNinja->getNode()->addAnimator(smgr->createCollisionResponseAnimator(NULL, redNinja->getNode(), radius));

	updateList.push_back(redNinja);

	redNinja->move(player);

#ifdef DEBUG
	std::cout << "\nBadNinja spawned.\n";
#endif
}

// Function to spawn Monster instance.
void Game::spawnMonster(Player* player, IrrlichtDevice* device, ISceneManager* smgr, IVideoDriver* driver)
{
	++numOfEnemies;
	bool bMatched;

	vector3df position = vector3df(0, 80, 0);

	GameObject* ptr = NULL;

	list<GameObject*>::Iterator it = list<GameObject*>::Iterator();
	list<GameObject*>::Iterator tempIterator = list<GameObject*>::Iterator();
	it = updateList.begin();

	srand(time(NULL));

	while (true)
	{
		bMatched = false;

		for (int i = 0; i < updateList.getSize(); ++i)
		{
			if (tempIterator.operator==(it))
			{
				break;
			}

			ptr = dynamic_cast<Enemy*>(it.operator*());

			if (ptr != NULL)
			{
				if (ptr->getPosition() == position)
				{
					bMatched = true;
					break;
				}
			}

			if (tempIterator.operator==(it.operator++()))
			{
				break;
			}
		}

		if (!bMatched && (position - player->getPosition()).getLengthSQ() > 250000.0f)
		{
			break;
		}

		position = vector3df(10 + (rand() % 90), 80, 10 + (rand() % 90));
	}

	monster = new Monster(position, 0.1f, smgr, player, device);
	monster->loadModel(smgr->getMesh("Models/faerie.md2"), driver->getTexture("Textures/faerie2.bmp"));
	updateList.push_back(monster);
	const aabbox3df & boxForMonster = monster->getNode()->getBoundingBox();
	vector3df radius = boxForMonster.MaxEdge - boxForMonster.getCenter();
	monster->getNode()->addAnimator(smgr->createCollisionResponseAnimator(selector, monster->getNode(), radius));

#ifdef DEBUG
	std::cout << "\nMonster spawned.\n";
#endif
}

// Function to spawn BadFaerie instance.
void Game::spawnBadFaerie(Player* player, IrrlichtDevice* device, ISceneManager* smgr, IVideoDriver* driver)
{
	++numOfEnemies;

	bool bMatched;

	vector3df position = vector3df(0, 80, 0);

	GameObject* ptr = NULL;

	list<GameObject*>::Iterator it = list<GameObject*>::Iterator();
	list<GameObject*>::Iterator tempIterator = list<GameObject*>::Iterator();
	it = updateList.begin();

	srand(time(NULL));
	while (true)
	{
		bMatched = false;

		for (int i = 0; i < updateList.getSize(); ++i)
		{
			if (tempIterator.operator==(it))
			{
				break;
			}

			ptr = dynamic_cast<Enemy*>(it.operator*());

			if (ptr != NULL)
			{
				if (ptr->getPosition() == position)
				{
					bMatched = true;
					break;
				}
			}

			if (tempIterator.operator==(it.operator++()))
			{
				break;
			}
		}

		if (!bMatched && (position - player->getPosition()).getLengthSQ() > 250000.0f)
		{
			break;
		}

		position = vector3df(100 + (rand() % 900), 80, 100 + (rand() % 900));
	}

	// Setting up BadFaerie.
	badFaerie = new BadFaerie(position, 0.1f, smgr, player, device, &updateList, device->getVideoDriver());
	badFaerie->loadModel(smgr->getMesh("Models/faerie.md2"), driver->getTexture("Textures/faerie.bmp"));
	updateList.push_back(badFaerie);
	const aabbox3df & box2 = badFaerie->getNode()->getBoundingBox();
	vector3df radius = box2.MaxEdge - box2.getCenter();
	badFaerie->getNode()->addAnimator(smgr->createCollisionResponseAnimator(selector, badFaerie->getNode(), radius));

#ifdef DEBUG
	std::cout << "\nBadFaerie spawned.\n";
#endif
}

// Function to spawn Wraith instance.
void Game::spawnWraith(Player* player, IrrlichtDevice* device, ISceneManager* smgr, IVideoDriver* driver)
{
	++numOfEnemies;

	bool bMatched;

	vector3df position = vector3df(0, 80, 0);

	GameObject* ptr = NULL;

	list<GameObject*>::Iterator it = list<GameObject*>::Iterator();
	list<GameObject*>::Iterator tempIterator = list<GameObject*>::Iterator();
	it = updateList.begin();

	srand(time(NULL));
	while (true)
	{
		bMatched = false;

		for (int i = 0; i < updateList.getSize(); ++i)
		{
			if (tempIterator.operator==(it))
			{
				break;
			}

			ptr = dynamic_cast<Enemy*>(it.operator*());

			if (ptr != NULL)
			{
				if (ptr->getPosition() == position)
				{
					bMatched = true;
					break;
				}
			}

			if (tempIterator.operator==(it.operator++()))
			{
				break;
			}
		}

		if (!bMatched && (position - player->getPosition()).getLengthSQ() > 250000.0f)
		{
			break;
		}

		position = vector3df(100 + (rand() % 900), 80, 100 + (rand() % 900));
	}

	// Setting up Wraith.
	wraith = new Wraith(position, 1.0f, smgr, player, device, &updateList, device->getVideoDriver());
	wraith->loadModel(smgr->getMesh("Models/demon-body.md2"), driver->getTexture("Textures/demon.bmp"));
	updateList.push_back(wraith);
	const aabbox3df & boxForWraith = wraith->getNode()->getBoundingBox();
	vector3df radius = boxForWraith.MaxEdge - boxForWraith.getCenter();
	wraith->getNode()->addAnimator(smgr->createCollisionResponseAnimator(selector, wraith->getNode(), radius));

#ifdef DEBUG
	std::cout << "\nWraith spawned.\n";
#endif
}

void Game::displayMainMenu(GameState & gameState, IrrlichtDevice* device)
{
	IGUIEnvironment* guienv = device->getGUIEnvironment();

	IGUISkin* skin = guienv->getSkin();
	IGUIFont* font = guienv->getFont("Textures/fonthaettenschweiler.bmp");
	if (font)
		skin->setFont(font);

	skin->setFont(guienv->getBuiltInFont(), EGDF_TOOLTIP);

	guienv->addImage(device->getVideoDriver()->getTexture("Textures/background.jpg"), vector2d<s32>(-195, 0), false);

	guienv->addButton(rect<s32>(380, 200, 620, 270), NULL, GUI_ID_PLAY_BUTTON, L"Play");
	guienv->addButton(rect<s32>(380, 300, 620, 370), NULL, GUI_ID_INSTRUCTIONS_BUTTON, L"About");
	guienv->addButton(rect<s32>(380, 400, 620, 470), NULL, GUI_ID_CONTROLS_BUTTON, L"Controls");
	guienv->addButton(rect<s32>(380, 500, 620, 570), NULL, GUI_ID_QUIT_BUTTON, L"Exit");
	
}
