#pragma once

#include "ScreenState.h"
#include "Button.h"
#include "GameEngine.h"
#include "SDL_TTF.h"
#include "GameState.h"
#include <vector>

using namespace std;

class GameOverState : public ScreenState
{
private:
	vector<Button*> m_buttons;
	enum btn { playagain};

	bool m_winner = false;
	int m_score = 0;

public:

	GameOverState() {}
	GameOverState(bool winner, int score) 
		: m_winner(winner), m_score(score){}

	void Update(); // A 'pure virtual' method.
	void Render();
	void Enter();
	void Exit() {};
	void Resume() {};


};