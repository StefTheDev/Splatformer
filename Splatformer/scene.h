#pragma once
#include "Utilities.h"

class Vector2D;
class GameObject;

class Scene {
public:
	virtual void Update() = 0;
	virtual void Render() = 0;

	//Used to break up SDL events into separate Scene function calls
	void HandleEvents(SDL_Event sdlEvent);

	//Event fired when a gamepad button is pressed. Uses SDL_GameControllerButton
	virtual void ButtonDown(SDL_JoystickID gamepadID, Uint8 button);
	//Event fired when a gamepad button is released. Uses SDL_GameControllerButton
	virtual void ButtonUp(SDL_JoystickID gamepadID, Uint8 button);
	//Event fired when a gamepad left stick is moved
	virtual void LeftStick(SDL_JoystickID gamepadID, Vector2D axisPosition);
	//Event fired when a gamepad right stick is moved
	virtual void RightStick(SDL_JoystickID gamepadID, Vector2D axisPosition);
	//Event fired when a gamepad left trigger is adjusted
	virtual void LeftTrigger(SDL_JoystickID gamepadID, float triggerPosition);
	//Event fired when a gamepad right trigger is adjusted
	virtual void RightTrigger(SDL_JoystickID gamepadID, float triggerPosition);
	//Event fired when a gamepad is plugged in
	virtual void ControllerAdded(SDL_JoystickID gamepadID);
	//Event fired when a gamepad is unplugged
	virtual void ControllerRemoved(SDL_JoystickID gamepadID);
	//Event fired when a gamepad's ID is changed
	virtual void ControllerRemapped(SDL_JoystickID gamepadID);
	//Event fired when game is quit
	virtual void Quit();

protected:
	std::vector<GameObject> objects;
};