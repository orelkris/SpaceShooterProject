#include "GameEngine.h"
#include <cstdlib>
#include <ctime>
#include "MainMenuState.h"


// in video this is called Game.cpp
GameEngine* GameEngine::Instance()
{
	static GameEngine* instance;
	if (instance == nullptr)
		instance = new GameEngine();

	return instance;
}


// in video this is called Init() with some parameters
// to set the video size and such
bool GameEngine::InitGameEngine()
{
	window = SDL_CreateWindow("First SDL App", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH, WINDOW_HEIGHT, 0);
	if (!window)
	{
		cout << "Window initialization failed.\n";
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer)
	{
		cout << "Renderer initialization failed.\n";
		return false;
	}

	//check if TTF engine can be used.... if it can't be initialized, return false
	if (TTF_Init() != 0)
	{
		cout << "TTF Font init failed.\n";
		return false;
	}

	// this is for the engine itself
	if (Mix_Init(MIX_INIT_MP3) == 0)
	{
		cout << "Mixer init failed...\n";
	}
	else
	{
		// 4096 is the chunk size per buffer
		Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096);

		// dynamically allocation channels
		Mix_AllocateChannels(16);
	}

	isRunning = true;

	m_state = new StateMachine();
	m_state->ChangeState(new MainMenuState());

	m_iKeystates = SDL_GetKeyboardState(nullptr);

	return true;
}

// function that loads the texture
SDL_Texture* GameEngine::LoadTexture(const char* path)
{
	SDL_Surface* surface = IMG_Load(path);

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == NULL)
	{
		std::cout << "Error during texture generation: " << SDL_GetError() << std::endl;
		return NULL;
	}

	SDL_FreeSurface(surface);

	return texture;
}

SDL_Texture* GameEngine::LoadTextureWithColourKey(const char* path)
{
	SDL_Texture* texture = NULL;
	SDL_Surface* surface = IMG_Load(path);

	if (surface == NULL)
	{
		std::cout << "Error during texture generation: " << SDL_GetError() << std::endl;
		return NULL;
	}
	else
	{
		SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0xff, 0xff, 0xff));

		texture = SDL_CreateTextureFromSurface(renderer, surface);
	}

	SDL_FreeSurface(surface);

	return texture;
}

bool GameEngine::KeyDown(SDL_Scancode e)
{
	if (m_iKeystates == nullptr)
	{
		return false;
	}

	if (m_iKeystates[e] == 1)
	{
		return true;
	}

	return false;
}

bool GameEngine::KeyUp(SDL_Scancode e)
{
	if (m_iKeystates == nullptr)
	{
		return false;
	}

	if (m_iKeystates[e] == 0)
	{
		return true;
	}

	return false;
}


void GameEngine::Render()
{
	GetState()->Render();
}



// clean up
void GameEngine::Quit()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	//TTF_CloseFont(font);
	//Mix_CloseAudio();

	//shutdown SDL
	SDL_Quit();
	TTF_Quit();

}



void GameEngine::Input()
{
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_MOUSEMOTION) //if mouse movement is detected
		{
			SDL_GetMouseState(&mouseX, &mouseY);
			break;
		}

		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				leftMouse = true;
				break;
			}
		}

		if (event.type == SDL_MOUSEBUTTONUP)
		{
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				leftMouse = false;
			}

			break;
		}

		//if we click 'X' button to close the app window then SDL_QUIT event type is triggered
		if (event.type == SDL_QUIT)
		{
			isRunning = false;
		}


	}
}



void GameEngine::Update()
{
	GetState()->Update();
}



