#pragma once

#include "SDL_gamecontroller.h"

#include "Utilities.h"

struct GamePad
{
	bool buttons[SDL_CONTROLLER_BUTTON_MAX];
	int axis[SDL_CONTROLLER_AXIS_MAX];
};

enum Controllers
{
	PLAYER1,
	PLAYER2,
	PLAYER3,
	PLAYER4,
};

class Input
{
public:
	static Input* GetInstance();
	static void Destroy();
	bool IsControllerButtonPressed(Controllers _controllerID, SDL_GameControllerButton _button);
	bool IsControllerButtonHeld(Controllers _controllerID, SDL_GameControllerButton _button);
	float GetControllerAxis(Controllers _controllerID, SDL_GameControllerAxis _axis);
	void Initialise();
	void Process();
	void HandleEvents(SDL_Event _event);
	int GetNumGamepads() { return numGamepads; }

private:
	static Input* instance;
	Input() {};
	~Input() {};
	std::vector<SDL_GameController*> connectedControllers;
	std::vector<GamePad> controllerInputs;
	std::vector<GamePad> lastControllerInputs;
	int numGamepads = 0;
};

