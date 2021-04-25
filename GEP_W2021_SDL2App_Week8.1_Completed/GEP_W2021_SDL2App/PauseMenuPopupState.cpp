#include "PauseMenuPopupState.h"
#include "GameEngine.h"
#include "MainMenuState.h"

void PauseMenuPopupState::Enter()
{

	m_buttons.push_back(new Button("Assets/Textures/resume.png", { 0,0,200,80 },
		{ GameEngine::Instance()->GetScreenWidth() / 4, GameEngine::Instance()->GetScreenHeight() / 4, 400, 100 }));

	m_buttons.push_back(new Button("Assets/Textures/exit.png", { 0,0,400,100 },
		{ GameEngine::Instance()->GetScreenWidth() / 4, GameEngine::Instance()->GetScreenWidth() / 4 + 100, 400, 100 }));
}

void PauseMenuPopupState::Update()
{
	// Update buttons. Allows for mouseovers
	for (int i = 0; i < (int)m_buttons.size(); ++i)
	{
		m_buttons[i]->Update();
	}

	// what happens when we click resume
	if (m_buttons[btn::resume]->Clicked())
	{
		GameEngine::Instance()->GetState()->PopState();
	}
	
	// go back to main menu
	else if (m_buttons[btn::exit]->Clicked())
	{
		// implement GameEngine::Instance()->Clean()//

		GameEngine::Instance()->GetState()->ChangeState(new MainMenuState);
	}
}

void PauseMenuPopupState::Render()
{
	//GameEngine::Instance()->GetState()->GetStates().front()->Render();

	// background is blended
	SDL_SetRenderDrawBlendMode(GameEngine::Instance()->GetRenderer(), SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(GameEngine::Instance()->GetRenderer(), 64, 64, 128, 128);

	// draw background
	SDL_Rect rect = { 150 , 78,
		GameEngine::Instance()->GetScreenWidth() / 2 + 100, GameEngine::Instance()->GetScreenHeight() / 2 + 100};
	SDL_RenderFillRect(GameEngine::Instance()->GetRenderer(), &rect);

	// draw buttons
	for (int i = 0; i < (int)m_buttons.size(); ++i)
	{
		m_buttons[i]->Render();
	}

	ScreenState::Render();
}


void PauseMenuPopupState::Exit()
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