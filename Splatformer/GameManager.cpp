#include "GameManager.h"
#include "SoundManager.h"

#include "SceneStorage.h"

GameManager* GameManager::gameManager = nullptr;


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

		if (TTF_Init() == -1) return false;

		scenes.push_back(std::make_unique<SceneStorage<MenuScene>>());
		scenes.push_back(std::make_unique<SceneStorage<Lobby>>());
		scenes.push_back(std::make_unique<SceneStorage<GameScene>>());

		scenes[MENU]->LoadScene(renderer);

		Input::GetInstance();
		Input::GetInstance()->Initialise();
	}

	SoundManager::Initialise();
	SoundManager::LoadSounds("Resources/Sounds");

	Switch(MENU);

	return true;
}

void GameManager::Render()
{
	SDL_RenderClear(renderer);

	scenes[gameState]->RenderScene(renderer);

	SDL_RenderPresent(renderer);
}

void GameManager::HandleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		Input::GetInstance()->HandleEvents(event);
		switch (event.type) {
		case SDL_QUIT:
		{
			gameState = EXIT;
		} break;
		default:
			break;
		}


		scenes[gameState]->HandleEvents(event);
	}
}

void GameManager::Process()
{
	SoundManager::Update();

	timeLastFrame = timeCurrentFrame;
	timeCurrentFrame = SDL_GetPerformanceCounter();

	deltaTime = (float)((timeCurrentFrame - timeLastFrame) / (float)SDL_GetPerformanceFrequency());


	scenes[gameState]->UpdateScene();
	Input::GetInstance()->Process();
}

void GameManager::CheckSwitch() {
	if (gameState == nextGameState) return;
	 
	scenes[gameState]->UnloadScene();

	gameState = nextGameState;

	scenes[gameState]->LoadScene(renderer);
}

void GameManager::Clean()
{
	SoundManager::ReleaseAll();

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	SDL_Quit();
}

void GameManager::Switch(GameState _gameState)
{
	nextGameState = _gameState;
}

GameManager* GameManager::GetInstance()
{
	if (gameManager == nullptr) gameManager = new GameManager();
	return gameManager;
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
