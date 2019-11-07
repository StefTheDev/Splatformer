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

	//Just storing it until we need it
	std::unique_ptr<UIButton> play;

private:
	SDL_TimerID waitTimer;

	bool canInteract = false;

	void Load(SDL_Renderer* gameRenderer) override;
	void Unload() override;
	void ButtonDown(SDL_JoystickID _gamepadID, Uint8 _button) override;
};