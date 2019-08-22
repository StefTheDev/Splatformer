#pragma once
#include "scene.h"

class SceneTest : public Scene {

	void ButtonDown(SDL_JoystickID gamepadID, Uint8 button) override;

	//std::map<SDL_JoystickID, Player> players;
};