#include "SpriteEx.h"
#include "GameEngine.h"


void SpriteExAnimated::Animate()
{
	m_iFrame++;

	if (m_iFrame == m_iFrameMax)
	{
		m_iFrame = 0;
		m_iSprite++;
		if (m_iSprite == m_iSpriteMax)
			m_iSprite = 0;

	}


}

void SpriteEx::Render()
{
	// if equal to 0 then it is successful
	if (SDL_RenderCopyEx(GameEngine::Instance()->GetRenderer(), texture, &spriteSrcRect, &spriteDestRect,
		angle, nullptr, SDL_FLIP_NONE) == 0)
	{
		//std::cout << "Success...\n";
	}
	else
	{
		//std::cout << "Failed...\n";
	}
 }

void SpriteEx::UpdateDestRect()
{
	// get center point in x and y of the sprite
	spriteDestRect.x = (int)(m_X - spriteDestRect.w * 0.5f);
	spriteDestRect.y = (int)(m_Y - spriteDestRect.h * 0.5f);
}
