#pragma once

#include "SpriteEx.h"

class Asteroid : public SpriteEx
{
private:
	float rotationSpeed; // at what speed should the asteroid rotate
	int asteroidHealth;
	bool isDead;
	int value;

	// Constructor
public:
	Asteroid(SDL_Texture* tex, SDL_Rect srcRect, SDL_Rect destRect, float rotSpeed, int randomScale, float sizeMult)
		: SpriteEx(tex, srcRect, destRect), rotationSpeed(rotSpeed)
	{
		m_X = destRect.x;
		m_Y = destRect.y;
		m_dRadius = 50 * sizeMult;
		// deprecate health? Kill asteroids based on size only?
		asteroidHealth = randomScale + 5;
		// 1, 10, 20, 30
		value = 1 + (randomScale * 10);
	}

	int getValue() { return value; }
	bool getisDead() { return isDead; }
	int getHealth() { return asteroidHealth; }
	void damageHealth()
	{
		asteroidHealth--;
		spriteDestRect.w -= 5;
		spriteDestRect.h -= 5;
		m_dRadius -= 5 / M_PI;

		if (asteroidHealth <= 0)
		{
			isDead = true;
		}

		// adjust scale
		if (spriteDestRect.w <= 0 || spriteDestRect.h <= 0)
		{
			asteroidHealth = 0;
			isDead = true;
		}

		// set a minimum radius of 5
		if (m_dRadius <= 0)
		{
			m_dRadius = 5;
		}

	}

	void Update()
	{
		angle += rotationSpeed; //nothing fancy in here yet...just incrementing the angle with rotationSpeed
	}
};