#pragma once
#include "Utilities.h"
#include "Vector2.h"
#include "Entity.h"
#include "UIButton.h"
#include "Camera.h"

class Scene {
public:
	void LoadScene(SDL_Renderer* gameRenderer);
	void UnloadScene();

	void UpdateScene();
	void RenderScene(SDL_Renderer* gameRenderer);
	
	//TODO: Draw background inside camera rect

	//Used to break up SDL events into separate Scene function calls
	void HandleEvents(SDL_Event sdlEvent);

	//Event fired when a gamepad button is pressed. Uses SDL_GameControllerButton
	virtual void ButtonDown(SDL_JoystickID gamepadID, Uint8 button);
	//Event fired when a gamepad button is released. Uses SDL_GameControllerButton
	virtual void ButtonUp(SDL_JoystickID gamepadID, Uint8 button);
	//Event fired when a gamepad left stick is moved
	virtual void LeftStick(SDL_JoystickID gamepadID, Vector2 axisPosition);
	//Event fired when a gamepad right stick is moved
	virtual void RightStick(SDL_JoystickID gamepadID, Vector2 axisPosition);
	//Event fired when a gamepad left trigger is adjusted
	virtual void LeftTrigger(SDL_JoystickID gamepadID, float triggerPosition);
	//Event fired when a gamepad right trigger is adjusted
	virtual void RightTrigger(SDL_JoystickID gamepadID, float triggerPosition);
	//Event fired when a gamepad is plugged in
	virtual void ControllerAdded(int _deviceIndex);
	//Event fired when a gamepad is unplugged
	virtual void ControllerRemoved(SDL_JoystickID instanceID);
	//Event fired when a gamepad's ID is changed
	virtual void ControllerRemapped(SDL_JoystickID instanceID);
	//Event fired when game is quit
	virtual void Quit();

	//Return a pointer to this scene's camera object
	Camera* GetCamera();

protected:
	virtual void Load(SDL_Renderer* gameRenderer) = 0;
	virtual void Unload() = 0;

	virtual void Update() = 0;
	virtual void Render(SDL_Renderer* gameRenderer) = 0;

	std::vector<std::unique_ptr<Entity>> objects;
	Camera camera;
};