#pragma once
#include "scene.h"
#include "player.h"

class Lobby : public Scene {
public:
	Lobby();

	void Update() override;
	void Render(SDL_Renderer* gameRenderer) override;

private:
	void Load(SDL_Renderer* gameRenderer) override;
	void Unload() override;

	std::map<SDL_JoystickID, Player> players;
};