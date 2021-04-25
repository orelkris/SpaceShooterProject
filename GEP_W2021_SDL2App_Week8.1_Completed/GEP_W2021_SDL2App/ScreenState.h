#pragma once

#include <SDL.h>
#include <sdl_ttf.h>
class ScreenState // This is the abstract base class for all specific states.
{
protected:
	TTF_Font * m_pFont;
	SDL_Texture* m_pFontTexture;
	SDL_Rect m_rFontRect;
	//SDL_Surface* m_pFontSurface;


public:
	virtual void Update() = 0; // A 'pure virtual' method.
	virtual void Render();
	void RenderFont(bool isRefreshText, const char *text, int x, int y);
	void RenderFontColor(bool isRefreshText, const char* text, int x, int y, SDL_Color textColor);
	virtual void Enter() = 0;
	virtual void Exit() = 0;
	virtual void Resume() = 0;
};