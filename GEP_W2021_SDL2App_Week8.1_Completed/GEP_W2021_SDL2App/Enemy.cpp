#include "Enemy.h"
#include "GameEngine.h"
#include <algorithm>


Enemy::Enemy(SDL_Texture* bulletTex, SDL_Texture* tex, double x, double y)
	: SpriteExAnimated(tex, x - 32, y - 32, 180, 0, 4, 0.1f)
{
	m_bulletTex = bulletTex;
	spriteSrcRect = { 0, 0, 64, 64 };
	spriteDestRect = { (int)(x - 32), (int)(y - 32), 64, 64 };
}

Enemy::~Enemy()
{

}

void Enemy::Render()
{
	// render bullets here

	this->SpriteExAnimated::Render(); // invoke the base class's Render()

	for (int i = 0; i < (int)m_bullets.size(); ++i)
	{
		m_bullets[i]->Render();
	}

	this->UpdateBullets();
	this->UpdateEnemy();
}

void Enemy::MoveForward()
{
	//m_DX = (float)cos((angle - 90) * M_PI / 180);

	m_DY = (float)sin((angle - 90) * M_PI / 180);

	// update the velocities
	//m_velX += m_DX * m_speed;
	m_velY += m_DY * m_dSpeed;

	// clamp the velocities
	//m_velX = min(max(m_velX, -(m_velMax * fabs(m_DX))), (m_velMax * fabs(m_DX)));
	m_velY = min(max(m_velY, -(m_velMax * fabs(m_DY))), (m_velMax * fabs(m_DY)));

}

void Enemy::UpdateBullets()
{
	for (int i = 0; i < (int)m_bullets.size(); ++i)
	{
		m_bullets[i]->Update();

		// going off screen
		if (m_bullets[i]->m_Y > GameEngine::Instance()->GetScreenHeight())
		{
			delete m_bullets[i];
			m_bullets[i] = nullptr;
			m_bullets.erase(m_bullets.begin() + i);
		}
	}

	m_bullets.shrink_to_fit();
}

void Enemy::SpawnBullet()
{
	// conerting the enemy spaceship's angle to deltaX and deltaY
	float dx = (float)cos((angle - 90) * M_PI / 180);

	float dy = (float)sin((angle - 90) * M_PI / 180);

	m_bullets.push_back(new Bullet(m_bulletTex, m_X, m_Y + 62, angle, dx, dy));
}

void Enemy::UpdateEnemy()
{
	this->MoveForward();

	//m_X += m_velX; // update x coordinate
	m_Y += m_velY; // update y coordinate
	this->UpdateDestRect();
	spriteSrcRect.y = spriteSrcRect.h * m_iSprite; // updates the animation


	// wrap-around y
	if (m_Y < (0 - this->spriteSrcRect.h))
	{
		m_Y = GameEngine::Instance()->GetScreenHeight() + this->spriteSrcRect.h;
	}
	else if (m_Y > (GameEngine::Instance()->GetScreenHeight() + this->spriteSrcRect.h))
	{
		m_Y = 0 - this->spriteSrcRect.h;
	}
}