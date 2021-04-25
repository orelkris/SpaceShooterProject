#include "GameOverState.h"

void GameOverState::Enter()
{
	GameEngine::Instance()->SetLeftMouse(false);

	m_buttons.push_back(new Button("Assets/Textures/playAgain.png", { 0,0,389,129 },
		{ GameEngine::Instance()->GetScreenWidth() / 4, GameEngine::Instance()->GetScreenWidth() / 4 + 200, 400, 100 }));
	
	// loading the font
	m_pFont = TTF_OpenFont("Assets/Fonts/LTYPE.TTF", 70); //30 is the initial font size
}

void GameOverState::Update()
{
	// Update buttons. Allows for mouseovers.

	m_buttons[0]->Update();

	if (m_buttons[btn::playagain]->Clicked())
	{
		// we need to switch to gamestate
		GameEngine::Instance()->GetState()->ChangeState(new GameState());
	}
}

void GameOverState::Render()
{
	SDL_SetRenderDrawColor(GameEngine::Instance()->GetRenderer(), 255, 255, 255, 255);
	SDL_RenderClear(GameEngine::Instance()->GetRenderer());

	m_buttons[0]->hasManyFrames = false;
	m_buttons[0]->Render();

	string outcome = "";
	SDL_Color textColor = { 100, 200, 50, 255 };

	if (!m_winner)
	{
		outcome = "YOU LOSE!";
	}
	else if(m_winner)
	{
		outcome = "YOU WIN!";
		string score = "Score: " + std::to_string(m_score);
		RenderFontColor(true, score.c_str(), GameEngine::Instance()->GetScreenWidth() / 4, GameEngine::Instance()->GetScreenWidth() / 4 + 50, textColor);
	}

	RenderFontColor(true, outcome.c_str(), GameEngine::Instance()->GetScreenWidth() / 4, GameEngine::Instance()->GetScreenWidth() / 4 - 50, textColor);

	ScreenState::Render();
}
