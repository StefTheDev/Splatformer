#include "sceneTest.h"


constexpr int velIterations = 8;
constexpr int posIterations = 3;

SceneTest::SceneTest() {
	b2Vec2 gravity(0.0f, -9.8f);

	sceneWorld = std::make_unique<b2World>(gravity);

	playerSprite = std::make_shared<Sprite>();
}

void SceneTest::Load(SDL_Renderer* _gameRenderer) {
	for (int i = 0; i < SDL_NumJoysticks(); ++i) {
		if (SDL_IsGameController(i)) {
			controllers.push_back(SDL_GameControllerOpen(i));
		}
	}

	playerSprite->Load("Resources/Sprites/player.png", _gameRenderer, false);
	player.Initialise({20.0f, 20.0f}, sceneWorld.get(), playerSprite);
}

void SceneTest::Unload() {
}

void SceneTest::Update() {
	sceneWorld->Step(deltaTime, velIterations, posIterations);

	player.Update(GetCamera());
}

void SceneTest::Render(SDL_Renderer* _gameRenderer) {
	player.Render(_gameRenderer);
}

void SceneTest::ButtonDown(SDL_JoystickID _gamepadID, Uint8 _button) {
	if (_button == SDL_CONTROLLER_BUTTON_A) {
		std::cout << "Pressed A" << std::endl;
	}
}

void SceneTest::RightTrigger(SDL_JoystickID _gamepadID, float _axisValue) {
	std::cout << "RTrigger Moved: " << _axisValue << std::endl;
}
