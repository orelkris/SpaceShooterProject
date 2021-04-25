#pragma once

#include "ScreenState.h"
#include "Button.h"
#include <vector>

using namespace std;

class MainMenuState : public ScreenState
{
private:
	vector<Button*> m_buttons;
	enum btn{play, exit};

public:

	MainMenuState() {}

	void Update(); // A 'pure virtual' method.
	void Render();
	void RenderFont(bool isRefreshText, const char* text, int x, int y);
	void RenderFontColor(bool isRefreshText, const char* text, int x, int y, SDL_Color textColor);
	void Enter();
	void Exit();
	void Resume() {};


};

