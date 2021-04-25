#include "GameState.h"
#include "GameEngine.h"
#include "PauseMenuPopupState.h"
#include "GameOverState.h"
#include "MainMenuState.h"

void GameState::Enter()
{
	// load the actual sound
	fireSound = Mix_LoadWAV("Assets/Audio/Fire.wav");

	engineSound = Mix_LoadWAV("Assets/Audio/Engines.wav");

	// to set the volume of each chunk
	Mix_VolumeChunk(fireSound, 40);


	// this means the engine sound is lower than the fire sound
	Mix_VolumeChunk(engineSound, 40);

	// loading the font
	m_pFont = TTF_OpenFont("Assets/Fonts/LTYPE.TTF", 30); //30 is the initial font size

	bgSpriteTex = GameEngine::Instance()->LoadTexture("Assets/Sprites/background.png");
	mainSpriteTex = GameEngine::Instance()->LoadTexture("Assets/Sprites/Sprites1.png");
	
	playerSpriteTex = GameEngine::Instance()->LoadTexture("Assets/Sprites/Sprites1.png");
	enemySpriteTex = GameEngine::Instance()->LoadTexture("Assets/Sprites/Sprites.png");
	healthSpriteTex = GameEngine::Instance()->LoadTexture("Assets/Sprites/heart.png");
	shieldSpriteTex = GameEngine::Instance()->LoadTextureWithColourKey ("Assets/Sprites/shield.png");

	// entire texture itself, the source
	SDL_Rect bgSrcRect = { 0,0,0,0 };

	// to get the width/height of the texture
	SDL_QueryTexture(bgSpriteTex, NULL, NULL, &bgSrcRect.w, &bgSrcRect.h);

	// where on screen do you want to draw the sprite
	SDL_Rect bgDestRect = { 0,0,0,0 };

	// want to draw the size of the entire window
	// use this function to get the window dimensions
	SDL_GetWindowSize(GameEngine::Instance()->GetWindow(), &bgDestRect.w, &bgDestRect.h);

	// construct background 
	bg = new SpriteEx(bgSpriteTex, bgSrcRect, bgDestRect);

	// initialize player
	player = new Player(playerSpriteTex, (bgDestRect.w * 0.5), (bgDestRect.h - 100));

	// initialize enemy
	enemy = new Enemy(mainSpriteTex, enemySpriteTex, (bgDestRect.w - 200), (74));


	//****** HEALTH********//
	SDL_Rect healthSrtRect = { 0,0,254, 254 };

	// width and height of the health is 64 by 64
	SDL_Rect healthDestRect = { 0, 0, 64, 64 };

	// seed the rand function
	srand(time(0));

	// rotation speed for health sprite
	float healthRotation = 5;

	// generate random x and y values for health sprite
	healthDestRect.x = (rand() % 700) + 1;
	healthDestRect.y = (rand() % 500) + 1;

	// health sprite should not spawn on top of the player
	if ((healthDestRect.x < 500 && healthDestRect.x > 300) && (healthDestRect.y < 550 && healthDestRect.y > 350))
	{
		cout << "Collision detected...asteroid updated" << endl;
		healthDestRect.x = ((healthDestRect.x + 150) > (GameEngine::Instance()->GetScreenWidth() - 66) ? GameEngine::Instance()->GetScreenWidth() - 66 : healthDestRect.x + 150);
		healthDestRect.y = ((healthDestRect.y + 150) > (GameEngine::Instance()->GetScreenHeight() - 66) ? GameEngine::Instance()->GetScreenHeight() - 66 : healthDestRect.y + 150);
	}

	// initialize Health after creating random coordinates
	health = new Health(healthSpriteTex, healthSrtRect, healthDestRect, healthRotation);



	//***SHIELD***//
	SDL_Rect shieldSrcRect = { 0, 0, 584, 441 };

	SDL_Rect shieldDestRect = { 0, 0, 100, 80 };

	srand(time(0));

	// rotation speed for shield sprite
	float shieldRotation = 3;

	// generate random x and y values for shield sprite
	shieldDestRect.x = (rand() % 200) + 1; // generate between 1 & 700 pixels
	shieldDestRect.y = (rand() % 300) + 1; // generate between 1 & 500 pixels

	// shield sprite should not spawn on top of the player
	if ((shieldDestRect.x < 500 && shieldDestRect.x > 300) && (shieldDestRect.y < 550 && shieldDestRect.y > 350))
	{
		cout << "Collision detected...asteroid updated" << endl;
		shieldDestRect.x = ((shieldDestRect.x + 150) > (GameEngine::Instance()->GetScreenWidth() - 66) ? GameEngine::Instance()->GetScreenWidth() - 66 : shieldDestRect.x + 150);
		shieldDestRect.y = ((shieldDestRect.y + 150) > (GameEngine::Instance()->GetScreenHeight() - 66) ? GameEngine::Instance()->GetScreenHeight() - 66 : shieldDestRect.y + 150);
	}

	Shield* shi = new Shield(shieldSpriteTex, shieldSrcRect, shieldDestRect);
	shields.push_back(shi);
	

	/****** asteroids ****/
	// Get the area where the player would spawn (used for constraining where asteroids can spawn)
	int startingXPos = bgDestRect.w * 0.5;
	int startingYPos = bgDestRect.h - 100;

	// Recall that 64x64 is the cell width/height of the asteroid on Sprites.png
	SDL_Rect asteroidSrcRect = { 124, 0, 100, 100 };
	SDL_Rect asteroidDestRect = { 0, 0, 100, 100 };

	//generate asteroids (maximum 5 asteroids?)
	for (int i = 0; i < 5; i++)
	{
		// At the start of each loop, the Asteroid scale should reset to 100%
		asteroidDestRect.w = 100;
		asteroidDestRect.h = 100;

		//generate random speed for the current asteroid's rotation
		/*float r = (1 - rand() % 2 * 2) * (rand() % 6 + 1);*/

		// Set a 'set' rotation speed
		float r = 2.5F;

		/* Set the asteroid's position */
		// if the rolled x and y positions of the asteroids is within player spawn area, re-roll until a valid value(s) is found. 
		// Note that valid values are within -150 to +150 of player's x and y values. TODO: Make this more elegant?
		bool isValidSpawn = false;

		// do the rolls
		asteroidDestRect.x = (rand() % 700) + 1;
		asteroidDestRect.y = (rand() % 500) + 1;

		// asteroid's xPos must be out of this range: startingXPos - 150 < startingXPos < startingXPos + 150
		// and then do the same check with the yPos
		if (!(asteroidDestRect.x >= startingXPos - 150 && asteroidDestRect.x <= startingXPos + 150) &&
			!(asteroidDestRect.y >= startingYPos - 150 && asteroidDestRect.y <= startingYPos + 150))
		{
			isValidSpawn = true;
		}

		int randomScale = (rand() % 3) + 0;		// generate an int between 0 to 3 

		// Get a random asteroid scale from the scale array based on the above
		float sizeMult = asteroidSizes[randomScale];

		// Now scale the asteroid based on the size multiplier
		asteroidDestRect.w = asteroidDestRect.w * sizeMult;
		asteroidDestRect.h = asteroidDestRect.h * sizeMult;

		Asteroid* ast = new Asteroid(mainSpriteTex, asteroidSrcRect, asteroidDestRect, r, randomScale, sizeMult);
		asteroids.push_back(ast); //push it into the vector (list of asteroids)
	}
}

void GameState::Update()
{

	if (GameEngine::Instance()->KeyDown(SDL_SCANCODE_ESCAPE) == 1)
	{
		GameEngine::Instance()->GetState()->PushState(new PauseMenuPopupState());
		return; // to make sure we don't run the game in background while in pause menu
	}
	
	if (lives <= 0)
	{
		// here is where we push the game over menu
		Mix_HaltChannel(15);
		GameEngine::Instance()->GetState()->PushState(new GameOverState());
		return;
	}

	if (asteroids.size() <= 0)
	{
		// here is where we push the game over menu
		Mix_HaltChannel(15);
		GameEngine::Instance()->GetState()->PushState(new GameOverState(true, score));
		return;
	}

	// this will initiate the asteroid rotation
	for (int i = 0; i < asteroids.size(); ++i)
	{
		asteroids[i]->Update();
	}

	if (player)
	{
		player->Update();
	}

	if (player)
	{
		this->CheckCollision();
	}

	if (GameEngine::Instance()->KeyDown(SDL_SCANCODE_SPACE) && player)
	{
		if ((player->counter % 4) == 0)
		{
			Mix_PlayChannel(-1, fireSound, 0);
			player->SpawnBullet();
		}

		player->counter += 1;

	}

	if (abs((player->GetX()) - (enemy->GetX() + 10)) < 10 && enemy)
	{
		if((enemy->counter % 10) == 0)
		{
			//cout << "SPAWN TIME";
			Mix_PlayChannel(-1, fireSound, 0);
			enemy->SpawnBullet();

			//cout << player->GetX() << "   ";
			//cout << enemy->GetX() << "   ";
		}

		enemy->counter += 1;
	}

	if (GameEngine::Instance()->KeyDown(SDL_SCANCODE_W))
	{
		if (!Mix_Playing(15)) // if channel 15 is not playing
		{
			Mix_PlayChannel(15, engineSound, -1); // loop the engine sound
		}
	}

	// engine sound
	if (GameEngine::Instance()->KeyUp(SDL_SCANCODE_W))
	{
		if (player)
		{
			Mix_FadeOutChannel(15, 250);
			player->SetIdle();
		}
	}

	//slow down by using SDL_Delay
	SDL_Delay(10); //pause the game loop for 10 milliseconds to slow down the game to a decent speed
}

void GameState::SetColor(SDL_Texture* mTexture, Uint8 red, Uint8 green, Uint8 blue)
{
	//Modulate texture
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}

bool GameState::CheckCollision()
{
	for (int i = 0; i < (int)shields.size(); i++)
	{
		//check for the player and shield collision
		if (CircleCollisionTest(player->GetX(), player->GetY(),
			shields[i]->GetX(), shields[i]->GetY(),
			player->GetRadius(), shields[i]->GetRadius()
		))
		{
			//there is a player-shield collision
			cout << "Player collided with a shield!\n";

			// delete the shields
			delete shields[i];
			shields[i] = nullptr;
			shields.erase(shields.begin() + i);

			isShieldUp = true;
			isShieldNew = true;
			cout << "Shields are up" << endl;

			delete shield;

			startTimer = SDL_GetTicks();

			shield = nullptr;

			shieldPickedUp = true;

			// change the colour of the plane to reflect the shield being in effect
			SetColor(playerSpriteTex, 0xFF, 0x00, 0x00);

			return true;
		}
	}


	if (health != nullptr)
	{
		// check for health and player collision
		if (CircleCollisionTest(player->GetX(), player->GetY(),
			health->GetX(), health->GetY(),
			player->GetRadius(), health->GetRadius()))
		{
			// we can delete the player...
			// eventually introduce a "life" system

			std::cout << "Player collided with an health booster!\n";
			lives++;

			delete health;

			health = nullptr;

			return true;
		}

	}

	// shield pick up should last 10 seconds
	if ((SDL_GetTicks() - startTimer) < protectionTimer && shieldPickedUp)
	{
		//std::cout << SDL_GetTicks() - startTimer << std::endl;
		return true;
	}
	else
	{
		SDL_SetTextureColorMod(playerSpriteTex, 255, 255, 255);
	}

	// check for the player and asteroid collision
	for (int i = 0; i < (int)asteroids.size(); ++i)
	{
		//if (player != nullptr)
		//{
			// there is a collision if this is true
		if (CircleCollisionTest(player->GetX(), player->GetY(),
			asteroids[i]->GetX(), asteroids[i]->GetY(),
			player->GetRadius(), asteroids[i]->GetRadius() + 10))
		{
			// we can delete the player...
			// eventually introduce a "life" system

			std::cout << "Player collided with an asteroid!\n";
			lives--;

			// where on screen do you want to draw the sprite
			if (lives >= 1)
			{
				player->SetX((GameEngine::Instance()->GetScreenWidth() * 0.5));
				player->SetY((GameEngine::Instance()->GetScreenHeight() - 100));

			}

			return true;
		}
	}


	// check for enemy bullet and player collision
	for (int b = 0; b < (int)enemy->GetBullets().size(); ++b)
	{
		Bullet* bullet = enemy->GetBullets()[b];


		if (CircleCollisionTest(player->GetX(), player->GetY(),
			bullet->GetX(), bullet->GetY(),
			player->GetRadius(), bullet->GetRadius()))
		{
			std::cout << "Player collided with an asteroid!\n";
			lives--;


			std::cout << "PLAYER WAS HIT";
			// where on screen do you want to draw the sprite
			if (lives >= 1)
			{
				player->SetX((GameEngine::Instance()->GetScreenWidth() * 0.5));
				player->SetY((GameEngine::Instance()->GetScreenHeight() - 100));
			}
		}
		return true;
	}

	if (enemy != nullptr)
	{
		// check for player and enemy collision
		if (CircleCollisionTest(player->GetX(), player->GetY(),
			enemy->GetX(), enemy->GetY(),
			player->GetRadius(), enemy->GetRadius()))
		{
			lives--;

			std::cout << "PLAYER COLLIDED WITH ENEMY";
			// where on screen do you want to draw the sprite
			if (lives >= 1)
			{
				player->SetX((GameEngine::Instance()->GetScreenWidth() * 0.5));
				player->SetY((GameEngine::Instance()->GetScreenHeight() - 100));
			}

			return true;
		}
	}


	bool isBreakOutOfLoop = false;

	//check for bullet and asteroid collision
	for (int b = 0; b < (int)player->GetBullets().size(); b++)
	{
		for (int i = 0; i < (int)asteroids.size(); i++)
		{
			Bullet* bullet = player->GetBullets()[b];

			//TO DO: Add an explosion effect on collision
			if (CircleCollisionTest(bullet->GetX(), bullet->GetY(),
				asteroids[i]->GetX() + 15, asteroids[i]->GetY(),
				bullet->GetRadius(), asteroids[i]->GetRadius()))
			{
				cout << "Bullet collided with an asteroid!!\n";
				cout << asteroids[i]->getHealth() << endl;
				asteroids[i]->damageHealth();
				cout << asteroids[i]->getHealth() << endl;

				// Did asteroid die from the hit?
				if (asteroids[i]->getisDead())
				{
					//add to score 
					score = score + (asteroids[i]->getValue());

					//clean/destroy the bullet on impact
					delete bullet;
					player->GetBullets()[b] = nullptr;
					player->GetBullets().erase(player->GetBullets().begin() + b);

					//destroy the asteroid 
					delete asteroids[i];
					asteroids[i] = nullptr;
					asteroids.erase(asteroids.begin() + i);

				}

				isBreakOutOfLoop = true;
			}

			if (isBreakOutOfLoop)
				break;
		}

		if (isBreakOutOfLoop)
			break;
	}

	if (isBreakOutOfLoop)
	{
		player->GetBullets().shrink_to_fit();
		asteroids.shrink_to_fit();
	}

	return false;
}

void GameState::Render()
{
	SDL_SetRenderDrawColor(GameEngine::Instance()->GetRenderer(), 255, 255, 255, 255);
	SDL_RenderClear(GameEngine::Instance()->GetRenderer()); //clear previously drawn frame

	bg->Render();


	// render each of the asteroids (we have 5 for now)
	for (int i = 0; i < asteroids.size(); ++i)
	{
		asteroids[i]->Render();
	}

	if (player)
	{
		player->Render();
	}

	if (enemy)
	{
		enemy->Render();
	}

	if (health)
	{
		health->Render();
	}

	// Time track
	prevTime = currentTime;
	currentTime = SDL_GetTicks();
	deltaTime = (currentTime - prevTime) / 1000.0f;

	frameTime += deltaTime;

	// have shields spawn every 3 secs
	if (frameTime >= 3.0f)
	{
		for (int i = 0; i < shields.size(); i++)
			//render the shields
			shields[i]->Render();
	}

	// render score and lives
	string scoreString = "Score: " + std::to_string(this->score);
	string liveString = "Lives: " + std::to_string(this->lives);

	RenderFont(true, scoreString.c_str(), 32, 50);
	RenderFont(true, liveString.c_str(), 600, 500);

	ScreenState::Render();
}

void GameState::Exit()
{
	// to-do:: de-allocate memory 
	TTF_CloseFont(m_pFont);

	Mix_CloseAudio();
	Mix_Quit();
	IMG_Quit();
}
