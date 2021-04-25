#pragma once
#include "SpriteEx.h"

class Bullet : public SpriteExAnimated
{
public:
	friend class Player;
	friend class Enemy;

	Bullet(SDL_Texture* tex, double x, double y, double a, double dx, double dy)
		: SpriteExAnimated(tex, x, y, a, 0, 0, 20.0f)
	{
		m_DX = dx;
		m_DY = dy;

		// the bullet sprite starts at 100 pixels on x axis, 0 on y and its 24 pixesl in width and height
		spriteSrcRect = { 100, 0, 24, 24 };

		spriteDestRect = { (int)(x - 12), (int)(y - 12), 24, 24 };

		m_dRadius = 8;
	}

	void Update()
	{
		m_X += (m_DX * m_dSpeed);
		m_Y += (m_DY * m_dSpeed);

		this->UpdateDestRect();
	}

};

