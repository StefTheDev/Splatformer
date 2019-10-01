#include "scene.h"

#include "player.h"
#include "Platform.h"
#include "Coin.h"

//Map a value, x, that exists between lower and upper, to a value between min and max
float MapBetween(float x, float lower, float upper, float min, float max) {
	return ((x - lower) / (upper - lower) * (max - min) + min);
}

void Scene::LoadScene(SDL_Renderer* _gameRenderer) {
	//Do something each time any scene is loaded
	Load(_gameRenderer);
}

void Scene::UnloadScene() {
	//Do something each time any scene is unloaded
	camera.SetPosition({ 0.0f, 0.0f });
	Unload();
}

void Scene::UpdateScene() {
	for (auto& entity : objects) {
		entity->Update();
	}

	Update();
}

void Scene::RenderScene(SDL_Renderer* _gameRenderer) {
	for (auto& entity : objects) {
		switch (entity->GetType()) {
		case PLAYER: static_cast<Player*>(entity.get())->Render(_gameRenderer); break;
		case PLATFORM: static_cast<Platform*>(entity.get())->Render(_gameRenderer); break;
		case COIN: static_cast<Coin*>(entity.get())->Render(_gameRenderer); break;
		case BUTTON: static_cast<UIButton*>(entity.get())->Render(_gameRenderer); break;
		}
	}

	Render(_gameRenderer);
}

void Scene::HandleEvents(SDL_Event _sdlEvent) {
	for (auto& entity : objects) {
		switch (entity->GetType()) {
			case PLAYER: static_cast<Player*>(entity.get())->Listen(_sdlEvent); break;
			case PLATFORM: static_cast<Platform*>(entity.get())->Listen(_sdlEvent); break;
			case BUTTON: static_cast<UIButton*>(entity.get())->Listen(_sdlEvent); break;
		}
	}


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
		case SDL_CONTROLLER_AXIS_LEFTX:
		case SDL_CONTROLLER_AXIS_LEFTY: {
			//TODO: Hand in a Vector2D with x and y mapped between -1.0f and 1.0f
			LeftStick(_sdlEvent.caxis.which, Vector2(0.0f, 0.0f));
			Vector2 absolutely;
			break;
		}
		case SDL_CONTROLLER_AXIS_RIGHTX:;
		case SDL_CONTROLLER_AXIS_RIGHTY:
		{
			//TODO: Hand in a Vector2D with x and y mapped between -1.0f and 1.0f
			RightStick(_sdlEvent.caxis.which, Vector2(0.0f, 0.0f));
			break;
		}
		case SDL_CONTROLLER_AXIS_TRIGGERLEFT:
		{
			LeftTrigger(_sdlEvent.caxis.which, MapBetween((float)_sdlEvent.caxis.value, -32768.0f, 32767.0f, -1.0f, 1.0f));
			break;
		}
		case SDL_CONTROLLER_AXIS_TRIGGERRIGHT:
		{
			RightTrigger(_sdlEvent.caxis.which, MapBetween((float)_sdlEvent.caxis.value, -32768.0f, 32767.0f, -1.0f, 1.0f));
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
	case SDL_CONTROLLERDEVICEREMOVED: {
		ControllerRemoved(_sdlEvent.cdevice.which);
		break;
	}
	case SDL_CONTROLLERDEVICEREMAPPED: {
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

void Scene::LeftStick(SDL_JoystickID _gamepadID, Vector2 _axisPosition) {
}

void Scene::RightStick(SDL_JoystickID _gamepadID, Vector2 _axisPosition) {
}

void Scene::LeftTrigger(SDL_JoystickID _gamepadID, float _triggerPosition) {
}

void Scene::RightTrigger(SDL_JoystickID _gamepadID, float _triggerPosition) {
}

void Scene::ControllerAdded(int _deviceIndex) {
}

void Scene::ControllerRemoved(SDL_JoystickID _instanceID) {
}

void Scene::ControllerRemapped(SDL_JoystickID _instanceID) {
}

void Scene::Quit() {
}

Camera* Scene::GetCamera() {
	return &camera;
}
