#include "sceneTest.h"


constexpr int velIterations = 8;
constexpr int posIterations = 3;

SceneTest::SceneTest() {
	b2Vec2 gravity(0.0f, -9.8f);

	sceneWorld = std::make_unique<b2World>(gravity);

	player = new Collider({0.0f, 0.0f});
	platform = new Collider({ 0.0f, -5.0f });
}

void SceneTest::Load() {
	player->InitialiseDynamic(sceneWorld.get(), 1.0f, 0.3f, 0.5f);
	platform->InitialiseStatic(sceneWorld.get());


	player->SetCollisionCategory(CATEGORY_PLAYER);
	player->SetCollisionMask(MASK_PLAYER_DEFAULT);

	platform->SetCollisionCategory(CATEGORY_PLATFORM);
	platform->SetCollisionMask(MASK_PLATFORM_NOCOLLIDE);

	for (int i = 0; i < SDL_NumJoysticks(); ++i) {
		if (SDL_IsGameController(i)) {
			controllers.push_back(SDL_GameControllerOpen(i));
		}
	}
}

void SceneTest::Unload() {
}

void SceneTest::Update() {
	sceneWorld->Step(deltaTime, velIterations, posIterations);
}

void SceneTest::Render() {
}

void SceneTest::ButtonDown(SDL_JoystickID _gamepadID, Uint8 _button) {
	if (_button == SDL_CONTROLLER_BUTTON_A) {
		std::cout << "Pressed A" << std::endl;
	}
}

void SceneTest::RightTrigger(SDL_JoystickID _gamepadID, float _axisValue) {
	std::cout << "RTrigger Moved: " << _axisValue << std::endl;
}
