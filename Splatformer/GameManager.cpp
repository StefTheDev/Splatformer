#include "GameManager.h"
#include "Jumper.h"

GameManager::GameManager()
{

}

GameManager::~GameManager()
{

}

bool GameManager::Initialise(std::string _title)
{
	Uint32 flags = SDL_WINDOW_SHOWN;
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		SDL_DisplayMode displayMode;
		SDL_GetCurrentDisplayMode(0, &displayMode);

		auto width = displayMode.w, height = displayMode.h;
		auto xPosition = (width - WINDOW_WIDTH) / 2, yPosition = (height - WINDOW_HEIGHT) / 2;

		window = SDL_CreateWindow(_title.c_str(), xPosition, yPosition, WINDOW_WIDTH, WINDOW_HEIGHT, flags);
		renderer = SDL_CreateRenderer(window, -1, 0);
		surface = SDL_GetWindowSurface(window);

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_UpdateWindowSurface(window);

		timeCurrentFrame = SDL_GetPerformanceCounter();

		gameState = MENU;

		inputManager.Initialise();

		testScene.LoadScene(renderer);
	}

	jumper = std::make_unique<Jumper>();
	if (!jumper->Initialise(renderer)) return false;

	return true;
}

void GameManager::Render()
{
	SDL_RenderClear(renderer);

	//Render things...
	testScene.Render(renderer);
	jumper->Render(renderer);

	SDL_RenderPresent(renderer);
}

void GameManager::HandleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		inputManager.HandleEvents(event);
		switch (event.type) {
		case SDL_QUIT:
		{
			gameState = EXIT;
		} break;
		default:
			break;
		}
		testScene.HandleEvents(event);
	}
}

void GameManager::Process()
{
	timeLastFrame = timeCurrentFrame;
	timeCurrentFrame = SDL_GetPerformanceCounter();

	deltaTime = (float)((timeCurrentFrame - timeLastFrame) / (float)SDL_GetPerformanceFrequency());

	testScene.Update();
	jumper->Update();
	std::cout << "A is held: " << inputManager.IsControllerButtonHeld(PLAYER1, SDL_CONTROLLER_BUTTON_A) << std::endl;
	// call this last
	inputManager.Process();
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

SDL_Window * GameManager::GetWindow()
{
	return window;
}

SDL_Renderer* GameManager::GetRenderer()
{
	return renderer;
}

SDL_Surface * GameManager::GetSurface()
{
	return surface;
}
