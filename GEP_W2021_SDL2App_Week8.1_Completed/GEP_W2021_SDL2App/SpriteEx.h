#pragma once
#include <SDL.h>
#include <iostream>
// Base cass will render just one static sprite
class SpriteEx
{

protected:
	SDL_Rect spriteSrcRect; // part of the spritesheet we would like to render
	SDL_Rect spriteDestRect; // position on the window we would like to render this sprite at
	SDL_Texture* texture; // reference to loaded texture

	int m_frameMax;
	int m_spriteMax;
	double m_X;
	double m_Y;
	double angle; // the angle to display the sprite in degrees
	double m_DX{}; // the change in x coordinate
	double m_DY{}; // the change in y cooridinate
	double m_dSpeed; // speed in pixels to move per change
	double m_dRadius;

public:

	SpriteEx(SDL_Texture* tex, SDL_Rect srcRect, SDL_Rect destRect)
		:spriteSrcRect(srcRect), spriteDestRect(destRect), texture(tex)
	{

	}

	SpriteEx(SDL_Texture* tex, double x, double y, double a = 0, int frameMax = 0, int spriteMax = 0, double speed = 0)
		: texture(tex), m_X(x), m_Y(y), angle(a), m_frameMax(frameMax), m_spriteMax(spriteMax), m_dSpeed(speed)
	{

	}

	double GetRadius() { return m_dRadius; }
	double GetX() { return m_X; }
	double GetY() { return m_Y; }

	void SetX(double x)
	{
		m_X = x;
	}

	void SetY(double y)
	{
		m_Y = y;
	}

	void Render();

	void UpdateDestRect();
	
};


// this is the animated version of the SpriteEx class.
// We inherit from the above class and add animation features
class SpriteExAnimated : public SpriteEx
{

protected:
	int m_iSprite = 0; // which sprite to display
	int m_iSpriteMax; // how many sprites in total
	int m_iFrame = 0; // which frame we are at now
	int m_iFrameMax;  // number of frames for this sprite

public:
	SpriteExAnimated(SDL_Texture* tex, double x, double y, double a, int frameMax, int spriteMax, double speed)
		: SpriteEx(tex, x, y, a, frameMax, spriteMax, speed)
	{


	}

	void Animate();
};

