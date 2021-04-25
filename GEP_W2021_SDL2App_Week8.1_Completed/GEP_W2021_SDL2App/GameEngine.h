#pragma once

#include "SDL.h"
#include <SDL_ttf.h>
#include <iostream>
#include <string>
#include "SpriteEx.h"
#include "Asteroid.h"
#include <vector>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "Player.h"
#include "StateMachine.h"

using namespace std;

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600


class GameEngine
{
private:
	bool isRunning = true;
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event event; //to handle events

	StateMachine* m_state;

	const Uint8* m_iKeystates; // manages keystates

	int mouseX, mouseY; // variables to hold mouse positions
	bool leftMouse = false; // keep track of left mouse button state

	 
public:

	SDL_Texture* LoadTexture(const char* path);
	SDL_Texture* LoadTextureWithColourKey(const char* path);

	int GetScreenWidth()
	{
		return WINDOW_WIDTH;
	}

	int GetScreenHeight()
	{
		return WINDOW_HEIGHT;
	}

	//This function returns the static instance we create the first time it is called.
	//All subsequent calls to the Instance() simply returns our first created GameEngine instance
	static GameEngine* Instance();

	SDL_Window* GetWindow() { return window; }

	bool IsRunning() { return isRunning; }
	void StopRunning(){ isRunning = false; }

	bool InitGameEngine();
	void InitGameWorld();

	SDL_Renderer* GetRenderer() { return renderer; }

	bool KeyDown(SDL_Scancode e);
	bool KeyUp(SDL_Scancode e);

	bool CheckCollision();

	void RenderFont(bool isRefreshText, const char* text, int x, int y);
	
	void Respawn();

	int GetMouseX() { return mouseX; }
	int GetMouseY() { return mouseY; }
	int GetLeftMouse(){ return leftMouse; }
	void SetLeftMouse(bool b) { leftMouse = b; }

	bool CircleCollisionTest(double x1, double y1, double x2, double y2, double r1, double r2);

	StateMachine* GetState() { return m_state; }

	void Input();
	void Update();
	void Render();
	void Quit();
};
