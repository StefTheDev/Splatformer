#include "GameManager.h"

GameManager::GameManager()
{

}

GameManager::~GameManager()
{

}

void GameManager::Initialise(std::string _title)
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

		SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));
		SDL_UpdateWindowSurface(window);

		timeCurrentFrame = SDL_GetPerformanceCounter();

		gameState = MENU;

		inputManager.Initialise();
	}
	else
	{
		gameState = EXIT;
	}

	//InitialiseGamepads();
}

void GameManager::Render()
{
	SDL_RenderClear(renderer);
	
	//Render things...

	SDL_RenderPresent(renderer);
}

void GameManager::HandleEvents()
{

	inputManager.HandleEvents();
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT: {
		gameState = EXIT;
	} break;

	//case SDL_CONTROLLERDEVICEADDED:
	//	std::cout << "DEVICEADDED cdevice.which = " << event.cdevice.which << std::endl;
	//	break;
	//case SDL_CONTROLLERBUTTONDOWN:
	//	// cycle through the controllers
	//	for (int i = 0; i < numGamepads; i++)
	//	{
	//		// Looking for the button that was pressed
	//		if (event.cbutton.which == SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(connectedControllers[i])))
	//		{
	//			// so the relevant state can be updated
	//			controllerInputs[i].buttons[event.cbutton.button] = true;
	//			//std::cout << "BUTTON DOWN = " << event.cbutton.button << std::endl;
	//		}
	//	}
	//	break;
	//	// Do the same for releasing a button
	//case SDL_CONTROLLERBUTTONUP:
	//	for (int i = 0; i < numGamepads; i++)
	//	{
	//		if (event.cbutton.which == SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(connectedControllers[i])))
	//		{
	//			controllerInputs[i].buttons[event.cbutton.button] = false;
	//			//std::cout << "BUTTON UP = " << event.cbutton.button << std::endl;
	//		}
	//	}
	//	break;

	//	// And axis motions
	//case SDL_CONTROLLERAXISMOTION:
	//	for (int i = 0; i < numGamepads; i++) {
	//		if (event.cbutton.which == SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(connectedControllers[i]))) {
	//			controllerInputs[i].axis[event.caxis.axis] = event.caxis.value;
	//			//std::cout << "AXIS" << std::endl;
	//		}
	//	}
	//	break;

	default:
		break;
	}

}

void GameManager::Process()
{
	timeLastFrame = timeCurrentFrame;
	timeCurrentFrame = SDL_GetPerformanceCounter();

	deltaTime = (float)((timeCurrentFrame - timeLastFrame) / (float)SDL_GetPerformanceFrequency());


	// call this last
	inputManager.Process();
	//// Updates previous states for input
	//for (int i = 0; i < numGamepads; i++)
	//{
	//	for (int a = 0; a < SDL_CONTROLLER_AXIS_MAX; a++)
	//	{
	//		lastControllerInputs[i].axis[a] = controllerInputs[i].axis[a];
	//	}
	//	for (int b = 0; b < SDL_CONTROLLER_BUTTON_MAX; b++)
	//	{
	//		lastControllerInputs[i].buttons[b] = controllerInputs[i].buttons[b];
	//	}
	//}
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

//void GameManager::InitialiseGamepads()
//{
//	if (SDL_WasInit(SDL_INIT_GAMECONTROLLER) != 1)
//	{
//		SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER);
//	}
//
//	int nJoysticks = SDL_NumJoysticks();
//	numGamepads = 0;
//
//	//Count how many controllers there are
//	for (int i = 0; i < nJoysticks; i++)
//	{
//		if (SDL_IsGameController(i))
//		{
//			numGamepads++;
//		}
//	}
//
//	// if we have some controllers attached
//	if (numGamepads > 0)
//	{
//		for (int i = 0; i < numGamepads; i++)
//		{
//			// Open the controller and add it to our list
//			SDL_GameController* pad = SDL_GameControllerOpen(i);
//			if (SDL_GameControllerGetAttached(pad) == 1)
//			{
//				connectedControllers.push_back(pad);
//			}
//			else
//				std::cout << "SDL_GetError() = " << SDL_GetError() << std::endl;
//		}
//		SDL_GameControllerEventState(SDL_ENABLE);
//	}
//
//	// Set vector sizes
//	controllerInputs.resize(numGamepads);
//	lastControllerInputs.resize(numGamepads);
//
//	// reset status of controllers
//	for (int i = 0; i < numGamepads; i++)
//	{
//		for (int a = 0; a < SDL_CONTROLLER_AXIS_MAX; a++)
//		{
//			controllerInputs[i].axis[a] = 0;
//			lastControllerInputs[i].axis[a] = 0;
//		}
//		for (int b = 0; b < SDL_CONTROLLER_BUTTON_MAX; b++)
//		{
//			controllerInputs[i].buttons[b] = false;
//			lastControllerInputs[i].buttons[b] = false;
//		}
//	}
//}

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