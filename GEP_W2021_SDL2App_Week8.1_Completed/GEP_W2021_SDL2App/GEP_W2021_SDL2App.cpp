// GEP_W2021_SDL2App.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "GameEngine.h"

int main(int argc, char* agv[])
{
	//In a non-singleton world, you would have had to create a game object for you to use GameEngine like this:
	//But when using a singleton, we don't create an object explicitly.

	if (!GameEngine::Instance()->InitGameEngine()) return -1;
	//GameEngine::Instance()->InitGameWorld();

	//Setup the Game loop
	while (GameEngine::Instance()->IsRunning())
	{
		GameEngine::Instance()->Input();
		GameEngine::Instance()->Update();
		GameEngine::Instance()->Render();

	}

	GameEngine::Instance()->Quit();

	return 0;
}
 




