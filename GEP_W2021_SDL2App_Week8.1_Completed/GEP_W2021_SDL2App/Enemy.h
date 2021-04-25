#pragma once

#include "SpriteEx.h"
#include <vector>
#include "Bullet.h"

using namespace std;

class Enemy : public SpriteExAnimated
{
protected:
	SDL_Texture* m_bulletTex;
	vector<Bullet*> m_bullets;
	void UpdateBullets();

	double m_velX = 0;
	double m_velY = 1;
	double m_velMax = 3;

	void MoveForward();


public:
	int counter;
	Enemy(SDL_Texture* bulletTex, SDL_Texture* tex, double x, double y);
	~Enemy();
	//void Update();
	void Render();
	void SpawnBullet();
	void UpdateEnemy();

	vector<Bullet*>& GetBullets()
	{
		return m_bullets;
	}
};

