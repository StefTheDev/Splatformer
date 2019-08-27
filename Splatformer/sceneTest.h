#pragma once
#include "scene.h"

#include "Player.h"

class SceneTest : public Scene {
public:
	SceneTest();

	void Update() override;
	void Render(SDL_Renderer* gameRenderer) override;

private:
	void Load(SDL_Renderer* _gameRenderer) override;
	void Unload() override;

	void ButtonDown(SDL_JoystickID gamepadID, Uint8 button) override;
	void RightTrigger(SDL_JoystickID gamepadID, float axisValue) override;

	//std::map<SDL_JoystickID, Player> players;
	std::unique_ptr<b2World> sceneWorld;

	std::shared_ptr<Sprite> playerSprite;
	Player player;

	std::vector<SDL_GameController*> controllers;
};