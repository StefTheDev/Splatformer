#pragma once
#include "scene.h"
#include "player.h"

//UI Entities
#include "UIButton.h"
#include "UIText.h"

class Lobby : public Scene 
{
public:
	Lobby();
	virtual ~Lobby() override;

	void Update() override;
	void Render(SDL_Renderer* gameRenderer) override;

	void ButtonDown(SDL_JoystickID gamepadID, Uint8 button) override;

private:
	void Load(SDL_Renderer* gameRenderer) override;
	void Unload() override;

	std::map<SDL_JoystickID, Player> players;
};