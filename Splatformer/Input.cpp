#include "Input.h"

Input* Input::instance = nullptr;

Input* Input::GetInstance() {
	if (instance == nullptr) instance = new Input();
	return instance;
}

void Input::Destroy() {
	if (instance != nullptr) {
		delete(instance);
	}
}

bool Input::IsControllerButtonPressed(Controllers _controllerID, SDL_GameControllerButton _button)
{
	if (_controllerID < 0 || _controllerID >= numGamepads) return false;

	return controllerInputs[_controllerID].buttons[_button] && !lastControllerInputs[_controllerID].buttons[_button];
}

bool Input::IsControllerButtonHeld(Controllers _controllerID, SDL_GameControllerButton _button)
{
	if (_controllerID < 0 || _controllerID >= numGamepads) return false;

	return controllerInputs[_controllerID].buttons[_button] && lastControllerInputs[_controllerID].buttons[_button];
}

float Input::GetControllerAxis(Controllers _controllerID, SDL_GameControllerAxis _axis)
{
	if (_controllerID < 0 || _controllerID >= numGamepads) return 0.0;

	return controllerInputs[_controllerID].axis[_axis] / 32768.0f;
}

void Input::Initialise()
{
	if (SDL_WasInit(SDL_INIT_GAMECONTROLLER) != 1)
	{
		SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER);
	}
	
	int nJoysticks = SDL_NumJoysticks();
	numGamepads = 0;
	
	//Count how many controllers there are
	for (int i = 0; i < nJoysticks; i++)
	{
		if (SDL_IsGameController(i))
		{
			numGamepads++;
		}
	}

	// Limit it to four
	if (numGamepads > 4) numGamepads = 4; // just in case more than 4 controllers are plugged in
	
	// if we have some controllers attached
	if (numGamepads > 0)
	{
		for (int i = 0; i < numGamepads; i++)
		{
			// Open the controller and add it to our list
			SDL_GameController* pad = SDL_GameControllerOpen(i);
			if (SDL_GameControllerGetAttached(pad) == 1)
			{
				connectedControllers.push_back(pad);
			}
			else
				std::cout << "SDL_GetError() = " << SDL_GetError() << std::endl;
		}
		SDL_GameControllerEventState(SDL_ENABLE);
	}
	
	// Set vector sizes
	controllerInputs.resize(numGamepads);
	lastControllerInputs.resize(numGamepads);
	
	// reset status of controllers
	for (int i = 0; i < numGamepads; i++)
	{
		for (int a = 0; a < SDL_CONTROLLER_AXIS_MAX; a++)
		{
			controllerInputs[i].axis[a] = 0;
			lastControllerInputs[i].axis[a] = 0;
		}
		for (int b = 0; b < SDL_CONTROLLER_BUTTON_MAX; b++)
		{
			controllerInputs[i].buttons[b] = false;
			lastControllerInputs[i].buttons[b] = false;
		}
	}
}

void Input::Process()
{
	// Updates previous states for input
	for (int i = 0; i < numGamepads; i++)
	{
		for (int a = 0; a < SDL_CONTROLLER_AXIS_MAX; a++)
		{
			lastControllerInputs[i].axis[a] = controllerInputs[i].axis[a];
		}
		for (int b = 0; b < SDL_CONTROLLER_BUTTON_MAX; b++)
		{
			lastControllerInputs[i].buttons[b] = controllerInputs[i].buttons[b];
		}
	}
}

void Input::HandleEvents(SDL_Event _event)
{
	switch (_event.type) {
		// This happens when a device is added
		// A future improvement is to cope with new controllers being plugged in
		// when the game is running
	case SDL_CONTROLLERDEVICEADDED:
		std::cout << "DEVICEADDED cdevice.which = " << _event.cdevice.which << std::endl;
		Initialise();
		break;

	case SDL_CONTROLLERDEVICEREMOVED:
		std::cout << "DEVICEREMOVED cdevice.which = " << _event.cdevice.which << std::endl;

		/*for (auto& controller : connectedControllers) {
			if(controller->)
		}*/
		connectedControllers.clear();
		Initialise();
		break;

		// If a controller button is pressed
	case SDL_CONTROLLERBUTTONDOWN:
		// Cycle through the controllers
		for (int i = 0; i < numGamepads; i++) {
			// Looking for the button that was pressed
			if (_event.cbutton.which == SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(connectedControllers[i]))) {
				// So the relevant state can be updated
				controllerInputs[i].buttons[_event.cbutton.button] = true;
				//std::cout << "BUTTON DOWN" << std::endl;
			}
		}
		break;

		// Do the same for releasing a button
	case SDL_CONTROLLERBUTTONUP:
		for (int i = 0; i < numGamepads; i++) {
			if (_event.cbutton.which == SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(connectedControllers[i]))) {
				controllerInputs[i].buttons[_event.cbutton.button] = false;
				//std::cout << "BUTTON UP" << std::endl;
			}
		}
		break;

		// And something similar for axis motion
	case SDL_CONTROLLERAXISMOTION:
		for (int i = 0; i < numGamepads; i++) {
			if (_event.cbutton.which == SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(connectedControllers[i]))) {
				controllerInputs[i].axis[_event.caxis.axis] = _event.caxis.value;
			}
		}
		break;
	}
}

void Input::AddController()
{
}
