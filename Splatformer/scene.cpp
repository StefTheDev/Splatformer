#include "scene.h"

void Scene::HandleEvents(SDL_Event _sdlEvent) {
	switch (_sdlEvent.type) {
	case SDL_CONTROLLERBUTTONDOWN: {
		ButtonDown(_sdlEvent.cbutton.which, _sdlEvent.cbutton.button);
		break;
	}
	case SDL_CONTROLLERBUTTONUP: {
		ButtonUp(_sdlEvent.cbutton.which, _sdlEvent.cbutton.button);
		break;
	}
	case SDL_CONTROLLERAXISMOTION: {
		switch (_sdlEvent.caxis.axis) {
		case SDL_CONTROLLER_AXIS_LEFTX:;
		case SDL_CONTROLLER_AXIS_LEFTY: {
			//TODO: Hand in a Vector2D with x and y mapped between -1.0f and 1.0f
			LeftStick(_sdlEvent.caxis.which, Vector2D());
			break;
		}
		case SDL_CONTROLLER_AXIS_RIGHTX:;
		case SDL_CONTROLLER_AXIS_RIGHTY:
		{
			//TODO: Hand in a Vector2D with x and y mapped between -1.0f and 1.0f
			RightStick(_sdlEvent.caxis.which, Vector2D());
			break;
		}
		case SDL_CONTROLLER_AXIS_TRIGGERLEFT:
		{
			LeftTrigger(_sdlEvent.caxis.which, MapBetween((float)_sdlEvent.caxis.axis, -32768.0f, 32767.0f, -1.0f, 1.0f));
			break;
		}
		case SDL_CONTROLLER_AXIS_TRIGGERRIGHT:
		{
			RightTrigger(_sdlEvent.caxis.which, MapBetween((float)_sdlEvent.caxis.axis, -32768.0f, 32767.0f, -1.0f, 1.0f));
			break;
		}
		default: break;
		}
		break;
	}
	case SDL_CONTROLLERDEVICEADDED: {
		ControllerAdded(_sdlEvent.cdevice.which);
		break;
	}
	case SDL_CONTROLLERDEVICEREMOVED:{
		ControllerRemoved(_sdlEvent.cdevice.which);
		break;
	}
	case SDL_CONTROLLERDEVICEREMAPPED:{
		ControllerRemapped(_sdlEvent.cdevice.which);
		break;
	}
	case SDL_QUIT: {
		Quit();
	}
	default: break;
	}
}

void Scene::ButtonDown(SDL_JoystickID _gamepadID, Uint8 _button) {
}

void Scene::ButtonUp(SDL_JoystickID _gamepadID, Uint8 _button) {
}

void Scene::LeftStick(SDL_JoystickID _gamepadID, Vector2D _axisPosition) {
}

void Scene::RightStick(SDL_JoystickID _gamepadID, Vector2D _axisPosition) {
}

void Scene::LeftTrigger(SDL_JoystickID _gamepadID, float _triggerPosition) {
}

void Scene::RightTrigger(SDL_JoystickID _gamepadID, float _triggerPosition) {
}

void Scene::ControllerAdded(SDL_JoystickID _gamepadID) {
}

void Scene::ControllerRemoved(SDL_JoystickID _gamepadID) {
}

void Scene::ControllerRemapped(SDL_JoystickID _gamepadID) {
}

void Scene::Quit() {
}
