#pragma once

#include "Utilities.h"

class StorageBase;
class MenuScene;
class GameScene;
class WinScene;
class Scene;

enum GameState
{
	MENU = 0,
	LOBBY,
	INGAME,
	WINNING,
	EXIT
};

const int FPS = 60;
const int FRAME_DELAY = 1000 / FPS;

class GameManager
{
public:
	GameManager() = default;
	~GameManager();

	bool Initialise(std::string _title);

	void Render();
	void HandleEvents();
	void Process();
	void CheckSwitch();
	void Clean();
	void Switch(GameState gameState);
	void SetWinner(int winner);

	SDL_Window * GetWindow();
	SDL_Renderer* GetRenderer();
	SDL_Surface* GetSurface();

	GameState GetState();
	int GetWinner() const;

	static GameManager* GetInstance();

private:
	SDL_Window * window;
	SDL_Renderer * renderer;
	SDL_Surface * surface;

	GameState gameState = MENU;
	GameState nextGameState = MENU;

	Uint64 timeCurrentFrame = 0;
	Uint64 timeLastFrame = 0;

	int winner = 0;

	//Input inputManager;
	std::vector<std::unique_ptr<StorageBase>> scenes;

	static GameManager* gameManager;
};
