#pragma once

#include "ScreenState.h"
#include <vector>
#include "Button.h"

using namespace std;

class PauseMenuPopupState : public ScreenState
{
private:
	vector<Button*> m_buttons;
	enum btn {resume, exit};

public:
	PauseMenuPopupState() {}

	void Update();
	void Render();
	void Enter();
	void Exit();
	void Resume() {};

};

