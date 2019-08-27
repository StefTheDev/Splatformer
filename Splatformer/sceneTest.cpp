#include "sceneTest.h"


constexpr int velIterations = 8;
constexpr int posIterations = 3;

SceneTest::SceneTest() {
	b2Vec2 gravity(0.0f, -19.6f);

	sceneWorld = std::make_unique<b2World>(gravity);
}

void SceneTest::Load(SDL_Renderer* _gameRenderer) {
	for (int i = 0; i < SDL_NumJoysticks(); ++i) {
		if (SDL_IsGameController(i)) {
			controllers.push_back(SDL_GameControllerOpen(i));
		}
	}

	playerSprite = std::make_shared<Sprite>("Resources/Sprites/player.png", _gameRenderer, false);
	player.Initialise({20.0f, 20.0f}, sceneWorld.get(), playerSprite);
	platform.Initialise({20.0f, -420.0f}, sceneWorld.get(), playerSprite);
}

void SceneTest::Unload() {
}

void SceneTest::Update() {
	sceneWorld->Step(deltaTime, velIterations, posIterations);

	player.Update(GetCamera());
	platform.Update(GetCamera());
}

void SceneTest::Render(SDL_Renderer* _gameRenderer) {
	player.Render(_gameRenderer);
	platform.Render(_gameRenderer);
}

void SceneTest::ButtonDown(SDL_JoystickID _gamepadID, Uint8 _button) {
	if (_button == SDL_CONTROLLER_BUTTON_A) {
		player.Jump();
	} else if (_button == SDL_CONTROLLER_BUTTON_B) {
		platform.SetCanCollide(!platform.CanCollide());
	}
}

void SceneTest::RightTrigger(SDL_JoystickID _gamepadID, float _axisValue) {
	std::cout << "RTrigger Moved: " << _axisValue << std::endl;
}
