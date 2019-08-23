#pragma once

#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "Utilities.h"



#include "sceneTest.h"


enum GameState
{
	MENU,
	INGAME,
	EXIT
};

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

const int FPS = 60;
const int FRAME_DELAY = 1000 / FPS;

class GameManager
{
public:
	GameManager();
	~GameManager();

	void Initialise(std::string _title);

	void Render();
	void HandleEvents();
	void Process();
	void Clean();

	SDL_Window * GetWindow();
	SDL_Renderer* GetRenderer();
	SDL_Surface* GetSurface();

	GameState GetState();

private:
	SDL_Window * window;
	SDL_Renderer * renderer;
	SDL_Surface * surface;

	GameState gameState;

	Uint64 timeCurrentFrame = 0;
	Uint64 timeLastFrame = 0;
};

#endif 