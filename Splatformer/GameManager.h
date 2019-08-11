#pragma once

#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "Utilities.h"

enum GameState
{
	MENU,
	INGAME,
	EXIT
};

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

class GameManager
{
public:
	GameManager(std::string);
	~GameManager();

	void Initialise(std::string _title);

	void Render();
	void Process();
	void Clean();

	GameState GetState();

private:
	SDL_Window * window;
	SDL_Renderer * renderer;
	SDL_Surface * surface;

	GameState gameState;
};

#endif 