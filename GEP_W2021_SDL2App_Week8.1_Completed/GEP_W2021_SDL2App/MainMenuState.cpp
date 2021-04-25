#include "MainMenuState.h"
#include "GameEngine.h"
#include "GameState.h"

void MainMenuState::Enter()
{
	GameEngine::Instance()->SetLeftMouse(false);

	m_buttons.push_back(new Button("Assets/Textures/play.png", { 0,0,400,100 },
		{ GameEngine::Instance()->GetScreenWidth() / 4, GameEngine::Instance()->GetScreenHeight() / 4, 400, 100 }));

	m_buttons.push_back(new Button("Assets/Textures/exit.png", { 0,0,400,100 }, 
		{ GameEngine::Instance()->GetScreenWidth() / 4, GameEngine::Instance()->GetScreenWidth() / 4 + 100, 400, 100 }));
}

void MainMenuState::Update()
{
	// Update buttons. Allows for mouseovers.
	for (int i = 0; i < (int)m_buttons.size(); ++i)
	{
		m_buttons[i]->Update();
	}

	if (m_buttons[btn::play]->Clicked())
	{
		// we need to switch to gamestate
		GameEngine::Instance()->GetState()->ChangeState(new GameState());
	}
	else if (m_buttons[btn::exit]->Clicked())
	{
		SDL_Delay(500);
		GameEngine::Instance()->StopRunning();
	}
}

void MainMenuState::Render()
{
	SDL_SetRenderDrawColor(GameEngine::Instance()->GetRenderer(), 255, 128, 0, 255);
	SDL_RenderClear(GameEngine::Instance()->GetRenderer());

	for (int i = 0; i < (int)m_buttons.size(); ++i)
	{
		m_buttons[i]->Render();
	}

	ScreenState::Render();
}

void MainMenuState::Exit()
{
	// when exiting a state make sure to clear everything in this state
	for (int i = 0; i < (int)m_buttons.size(); ++i)
	{
		delete m_buttons[i];
		m_buttons[i] = nullptr;
	}

	m_buttons.clear();
	m_buttons.shrink_to_fit();
}