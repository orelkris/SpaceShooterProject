#pragma once

#include "SpriteEx.h"
#include <vector>

class Shield : public SpriteEx
{
public:
	Shield(SDL_Texture* tex, SDL_Rect srcRect, SDL_Rect destRect)
		: SpriteEx(tex, srcRect, destRect)
	{
		m_X = destRect.x;
		m_Y = destRect.y;

		m_dRadius = 33;

	}
};