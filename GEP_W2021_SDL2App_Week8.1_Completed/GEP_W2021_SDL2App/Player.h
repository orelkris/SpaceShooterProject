#pragma once
#include "SpriteEx.h"
#include <vector>
#include "Bullet.h"

using namespace std;

class Player : public SpriteExAnimated
{

private:
	vector<Bullet*> m_bullets;
	void UpdateBullets();

	double m_velX = 0;
	double m_velY = 0;
	double m_velMax = 10;

public:
	int counter;

	Player(SDL_Texture* tex, double x, double y);
	~Player();

	SDL_Rect* getSpriteSrc()
	{
		return &spriteSrcRect;
	}

	void setSpriteSrc(float x, float y, float w, float h)
	{
		getSpriteSrc()->x = x;
		getSpriteSrc()->y = y;
		getSpriteSrc()->w = w;
		getSpriteSrc()->h = h;
	}

	void Update();
	void Render();
	void SetIdle();
	void SpawnBullet();
	void MoveForward();
	void MoveBackward();
	void UpdatePlayer();

	vector<Bullet*>& GetBullets()
	{
		return m_bullets;
	}

};

