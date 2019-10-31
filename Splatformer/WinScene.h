#pragma once

#include "scene.h"
#include "UIText.h"
#include "UIButton.h"

class WinScene : public Scene {
public:
	WinScene();
	virtual ~WinScene() override;

	void Update() override;
	void Render(SDL_Renderer* gameRenderer) override;

private:
	void Load(SDL_Renderer* gameRenderer) override;
	void Unload() override;
	void ButtonDown(SDL_JoystickID _gamepadID, Uint8 _button) override;
};