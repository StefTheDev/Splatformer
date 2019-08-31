#pragma once
#include "scene.h"

#include "Player.h"
#include "Platform.h"

class SceneTest : public Scene {
public:
	SceneTest();

	void Update() override;
	void Render(SDL_Renderer* gameRenderer) override;

private:
	void Load(SDL_Renderer* _gameRenderer) override;
	void Unload() override;

	void ButtonDown(SDL_JoystickID gamepadID, Uint8 button) override;
	void ButtonUp(SDL_JoystickID gamepadID, Uint8 button) override;
	void RightTrigger(SDL_JoystickID gamepadID, float axisValue) override;
	void LeftTrigger(SDL_JoystickID gamepadID, float axisValue) override;
	void ControllerAdded(int deviceIndex) override;

	//std::map<SDL_JoystickID, Player> players;
	std::unique_ptr<b2World> sceneWorld;
	PlatformingListener* contactListener;

	std::shared_ptr<Sprite> playerSprite;
	std::shared_ptr<Sprite> platformSprite;

	std::vector<SDL_GameController*> controllers;

	float timeElapsed;
};