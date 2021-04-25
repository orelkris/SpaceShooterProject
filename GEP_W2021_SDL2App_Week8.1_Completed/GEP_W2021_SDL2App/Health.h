#pragma once

#include "SpriteEx.h"

class Health : public SpriteEx
{

private:
	float rotationSpeed; // at what speed should the asteroid rotate

public:
	Health(SDL_Texture* tex, SDL_Rect srcRect, SDL_Rect destRect, float rotSpeed)
		: SpriteEx(tex, srcRect, destRect), rotationSpeed(rotSpeed)
	{
		m_X = destRect.x;
		m_Y = destRect.y;
		m_dRadius = 32;

	}

	void Update()
	{
	}

	void Render()
	{
		// render bullets here

		this->SpriteEx::Render(); // invoke the base class's Render()


		this->UpdateHealth();
	}

	void UpdateHealth()
	{
		angle += rotationSpeed;
	}

};

