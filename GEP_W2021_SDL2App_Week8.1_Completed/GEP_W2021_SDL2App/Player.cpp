#include "Player.h"
#include "GameEngine.h"
#include <algorithm> // for min/max functions


Player::Player(SDL_Texture* tex, double x, double y)
	: SpriteExAnimated(tex, x - 50, y - 50, 0, 1, 4, 0.1f)
{
	spriteSrcRect = { 0, 0, 100, 100 };
	spriteDestRect = { (int)(m_X - 50), (int)(m_Y - 50), 100, 100 };

	m_dRadius = 50;
}

Player::~Player()
{
	for (int i = 0; i < (int)m_bullets.size(); ++i)
	{
		delete m_bullets[i];
		m_bullets[i] = nullptr;
	}

	m_bullets.clear();
	m_bullets.shrink_to_fit();
}


void Player::Render()
{
	// rendering bullets here
	for (int i = 0; i < m_bullets.size(); ++i)
	{
		m_bullets[i]->Render();
	}


	this->SpriteExAnimated::Render();
}

void Player::SetIdle()
{
	spriteSrcRect.y = 0;
	m_iFrame = 0;
	m_iSprite = 0;
}

void Player::Update()
{
	// implement a rotation mechanism
	if (GameEngine::Instance()->KeyDown(SDL_SCANCODE_A))
	{
		angle -= 6.0;
	}
	else if (GameEngine::Instance()->KeyDown(SDL_SCANCODE_D))
	{
		angle += 6.0;
	}

	this->UpdatePlayer();
	this->UpdateBullets();

}

void Player::MoveForward()
{
	// converting the delta x and y of player directly
	m_DX = (float)cos((angle - 90) * M_PI / 180);

	m_DY = (float)sin((angle - 90) * M_PI / 180);

	// update the velocities
	m_velX += m_DX * m_dSpeed;

	m_velY += m_DY * m_dSpeed;

	// clamp the velocity so it doesn't exceed the max
	// maintain the previous velocity
	// take the minimum of two values 
	m_velX = min(max(m_velX, -(m_velMax * fabs(m_DX))), (m_velMax * fabs(m_DX)));

	m_velY = min(max(m_velY, -(m_velMax * fabs(m_DY))), (m_velMax * fabs(m_DY)));
}

void Player::MoveBackward()
{
	// converting the delta x and y of player directly
	m_DX = (float)cos((angle - 90) * M_PI / 180);

	m_DY = (float)sin((angle - 90) * M_PI / 180);

	// update the velocities
	m_velX -= m_DX * m_dSpeed;

	m_velY -= m_DY * m_dSpeed;

	// clamp the velocity so it doesn't exceed the max
	// maintain the previous velocity
	// take the minimum of two values 
	m_velX = min(max(m_velX, -(m_velMax * fabs(m_DX))), (m_velMax * fabs(m_DX)));

	m_velY = min(max(m_velY, -(m_velMax * fabs(m_DY))), (m_velMax * fabs(m_DY)));
}

void Player::UpdatePlayer()
{
	if (GameEngine::Instance()->KeyDown(SDL_SCANCODE_W))
	{
		spriteSrcRect.y = 100; // set y to the 100, which contains the second row of sprite animation
		this->Animate();
		this->MoveForward();
	}
	else if (GameEngine::Instance()->KeyDown(SDL_SCANCODE_S))
	{
		this->MoveBackward();
	}
	else
	{
		// add some drag to slow down until it comes to a complete stop
		m_velX *= 0.975;
		m_velY *= 0.975;

	}

	// wrap-around x
	if (m_X < (0 - this->spriteSrcRect.w))
	{
		m_X = GameEngine::Instance()->GetScreenWidth() + this->spriteSrcRect.w;
	}
	else if (m_X > (GameEngine::Instance()->GetScreenWidth() + this->spriteSrcRect.w))
	{
		m_X = 0 - this->spriteSrcRect.w;
	}

	// wrap-around y
	if (m_Y < (0 - this->spriteSrcRect.h))
	{
		m_Y = GameEngine::Instance()->GetScreenHeight() + this->spriteSrcRect.h;
	}
	else if (m_Y > (GameEngine::Instance()->GetScreenHeight() + this->spriteSrcRect.h))
	{
		m_Y = 0 - this->spriteSrcRect.h;
	}

	// update x and y coordinates
	m_X += m_velX;
	m_Y += m_velY;

	// update the destination rectangle
	this->UpdateDestRect();
	spriteSrcRect.x = spriteSrcRect.w * m_iSprite; // updates the animation itself
}

void Player::UpdateBullets()
{
	for (int i = 0; i < (int)m_bullets.size(); ++i)
	{
		m_bullets[i]->Update();

		// gone to the left of the screen or right most 
		// gone off screen on the vertical axis
		if (m_bullets[i]->m_X < 0 || m_bullets[i]->m_X > GameEngine::Instance()->GetScreenWidth() || 
			m_bullets[i]->m_Y < 0 || m_bullets[i]->m_Y > GameEngine::Instance()->GetScreenHeight())
		{
			delete m_bullets[i];
			m_bullets[i] = nullptr;
			m_bullets.erase(m_bullets.begin() + i);
		}
	}

	// shrink the vector
	m_bullets.shrink_to_fit();
}

void Player::SpawnBullet()
{

	// conerting the player spaceship's angle to deltaX and deltaY
	float dx = (float)cos((angle - 90) * M_PI / 180);

	float dy = (float)sin((angle - 90) * M_PI / 180);

	m_bullets.push_back(new Bullet(texture, m_X, m_Y, angle, dx, dy));
}

