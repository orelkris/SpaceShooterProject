#pragma once

#include "ScreenState.h"
#include <iostream>
#include "Player.h"
#include "Enemy.h"
#include "Health.h"
#include "Shield.h"
#include <SDL_mixer.h>
#include "Asteroid.h"

using namespace std;

class GameState : public ScreenState
{

private:
	Mix_Chunk* fireSound; // to play the fire sound
	Mix_Chunk* engineSound; // to play the engine sound

	SDL_Texture* mainSpriteTex; // load and store reference to the main sprite texture
	SDL_Texture* bgSpriteTex; // load and store background sprite tex reference
	SDL_Texture* enemySpriteTex; // load and store enemy sprite tex reference
	SDL_Texture* healthSpriteTex;
	SDL_Texture* shieldSpriteTex;
	SDL_Texture* playerSpriteTex;

	SpriteEx* bg; // background sprite to be drawn
	vector<Asteroid*> asteroids; // a vecotr of all asteroids we will have in the game 

	Player* player;

	Enemy* enemy;

	Health* health;

	Shield* shield;

	vector<Shield*> shields;

	float frameTime;
	bool isShieldUp;
	bool isShieldNew;
	float shieldFirstFrame;

	float asteroidSizes[4] = { 0.5, 1, 1.5, 2 };
	//float asteroidSizes[4] = {1, 2, 3, 4};
	int prevTime = 0;
	int currentTime;
	float deltaTime;

	int lives = 3;
	int score = 0;
	int protectionTimer = 10000;

	bool shieldPickedUp = false;

	int startTimer = 0;


public:
	GameState() {}
	void Update();
	void Render();
	void Enter();
	void Exit();
	void Resume() { cout << "Resuming Game..." << endl; };
	bool CircleCollisionTest(double x1, double y1, double x2, double y2, double r1, double r2)
	{
		return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)) < (r1 + r2));
	}
	void SetColor(SDL_Texture* texture, Uint8 red, Uint8 green, Uint8 blue);
	bool CheckCollision();
};

