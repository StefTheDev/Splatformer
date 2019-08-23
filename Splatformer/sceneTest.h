#pragma once
#include "scene.h"

#include "Collider.h"

class SceneTest : public Scene {
public:
	SceneTest();

	void Initialise();
	void Update() override;
	void Render() override;

private:
	void ButtonDown(SDL_JoystickID gamepadID, Uint8 button) override;
	void RightTrigger(SDL_JoystickID gamepadID, float axisValue) override;

	//std::map<SDL_JoystickID, Player> players;
	std::unique_ptr<b2World> sceneWorld;

	Collider* player;
	Collider* platform;

	SDL_GameController* controller = nullptr;
};