#include "GameManager.h"

GameManager::GameManager(std::string _title)
{
}

GameManager::~GameManager()
{
}

void GameManager::Initialise(std::string _title)
{
	Uint32 flags = SDL_WINDOW_FULLSCREEN;
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		SDL_DisplayMode displayMode;
		SDL_GetCurrentDisplayMode(0, &displayMode);

		auto width = displayMode.w, height = displayMode.h;
		auto xPosition = (width - WINDOW_WIDTH / 2), yPosition = (height - WINDOW_HEIGHT / 2);

		window = SDL_CreateWindow(_title.c_str(), xPosition, yPosition, WINDOW_WIDTH, WINDOW_HEIGHT, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		surface = SDL_GetWindowSurface(window);

		SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0x33, 0x33, 0x33));
		SDL_UpdateWindowSurface(window);
		SDL_Delay(8000);

		gameState = MENU;
	}
	else
	{
		gameState = EXIT;
	}
}

void GameManager::Render()
{
	SDL_RenderClear(renderer);

	//Render things...

	SDL_RenderPresent(renderer);
}

void GameManager::HandleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
		case SDL_QUIT: {
			gameState = EXIT;
		} break;
	default:
		break;
	}
}

void GameManager::Process()
{

}

void GameManager::Clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

GameState GameManager::GetState()
{
	return gameState;
}
