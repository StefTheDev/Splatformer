#include "scene.h"
#include <locale>

<<<<<<< Updated upstream
InputState thing[255];
InputState Scene::KeyState[255];
InputState Scene::SpecialKeyState[128];
=======
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
			//LeftStick(_sdlEvent.caxis.which, Vector2D());
			break;
		}
		case SDL_CONTROLLER_AXIS_RIGHTX:;
		case SDL_CONTROLLER_AXIS_RIGHTY:
		{
			//TODO: Hand in a Vector2D with x and y mapped between -1.0f and 1.0f
			//RightStick(_sdlEvent.caxis.which, Vector2D());
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
>>>>>>> Stashed changes

//std::chrono::time_point<std::chrono::system_clock> Scene::currTime;
//std::chrono::duration<double> Scene::deltaTimeDuration;
float Scene::deltaTime;

<<<<<<< Updated upstream
//glm::vec2 Scene::MousePos;
=======
/*
void Scene::LeftStick(SDL_JoystickID _gamepadID, Vector2D _axisPosition) {
}

void Scene::RightStick(SDL_JoystickID _gamepadID, Vector2D _axisPosition) {
}
*/
>>>>>>> Stashed changes

void Scene::UpdateGlobal() {
	//deltaTimeDuration = std::chrono::system_clock::now() - currTime;
	//currTime = std::chrono::system_clock::now();
	//deltaTime = deltaTimeDuration.count();
}

void Scene::UpdateDowns(unsigned char _key) {
	std::locale loc;
	KeyState[std::tolower(_key, loc)] = DOWN;
}

void Scene::UpdateUps(unsigned char _key) {
	std::locale loc;
	KeyState[std::tolower(_key, loc)] = UP;
}

void Scene::UpdateSpecialDowns(int _key) {
	SpecialKeyState[_key] = DOWN;
}

void Scene::UpdateSpecialUps(int _key) {
	SpecialKeyState[_key] = DOWN;
}

void Scene::UpdateMousePos(int _x, int _y) {
	//MousePos = glm::vec2(static_cast<float>(_x), static_cast<float>(_y));
}
