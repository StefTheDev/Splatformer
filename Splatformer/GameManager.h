#pragma once

#include "Utilities.h"

#include "sceneTest.h"
#include "MenuScene.h"

enum GameState
{
	MENU,
	INGAME,
	EXIT
};

const int FPS = 60;
const int FRAME_DELAY = 1000 / FPS;

class GameManager
{
public:
	GameManager();
	~GameManager();

	bool Initialise(std::string _title);

	void Render();
	void HandleEvents();
	void Process();
	void Clean();

	SDL_Window * GetWindow();
	SDL_Renderer* GetRenderer();
	SDL_Surface* GetSurface();

	GameState GetState();

	bool IsPaused() const;

private:
	SDL_Window * window;
	SDL_Renderer * renderer;
	SDL_Surface * surface;

	GameState gameState;

	Uint64 timeCurrentFrame = 0;
	Uint64 timeLastFrame = 0;

	//Input inputManager;

	SceneTest testScene;
	MenuScene menuScene;
};
