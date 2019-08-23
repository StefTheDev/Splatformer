#include "sceneTest.h"


constexpr int velIterations = 8;
constexpr int posIterations = 3;

SceneTest::SceneTest() {
	b2Vec2 gravity(0.0f, -9.8f);

	sceneWorld = std::make_unique<b2World>(gravity);

	player = new Collider({0.0f, 0.0f});
	platform = new Collider({ 0.0f, -5.0f });
}

void SceneTest::Initialise() {
	player->InitialiseDynamic(sceneWorld.get(), 1.0f, 0.3f, 0.5f);
	platform->InitialiseStatic(sceneWorld.get());


	for (int i = 0; i < SDL_NumJoysticks(); ++i) {
		if (SDL_IsGameController(i)) {
			controller = SDL_GameControllerOpen(i);
			if (controller) {
				break;
			} else {
				fprintf(stderr, "Could not open gamecontroller %i: %s\n", i, SDL_GetError());
			}
		}
	}
}

void SceneTest::Update() {
	sceneWorld->Step(deltaTime, velIterations, posIterations);
}

void SceneTest::Render() {
}

void SceneTest::ButtonDown(SDL_JoystickID _gamepadID, Uint8 _button) {
	if (_button == SDL_CONTROLLER_BUTTON_A) {
		player->Jump();
	}
}

void SceneTest::RightTrigger(SDL_JoystickID _gamepadID, float _axisValue) {
	std::cout << "RTrigger Moved: " << _axisValue << std::endl;
}
