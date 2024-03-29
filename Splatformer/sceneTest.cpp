#include "sceneTest.h"

#include "LevelLoader.h"

constexpr int velIterations = 8;
constexpr int posIterations = 3;

SceneTest::SceneTest() {
	b2Vec2 gravity(0.0f, -39.2f);

	contactListener = new PlatformingListener();

	sceneWorld = std::make_unique<b2World>(gravity);
	sceneWorld->SetContactListener(contactListener);
}

void SceneTest::Load(SDL_Renderer* _gameRenderer) {
	
	for (int i = 0; i < SDL_NumJoysticks(); ++i) {
		if (SDL_IsGameController(i)) {
			controllers.push_back(SDL_GameControllerOpen(i));
		}
	}

	textLabel = std::make_shared<TextLabel>("Test Scene", TTF_OpenFont("Resources/Fonts/Helvetica.ttf", 254), 
		SDL_Color{ 0, 255, 255},
		SDL_Rect{ 700, 60, 540, 100}
	);

	playerSprite = std::make_shared<Sprite>("Resources/Sprites/player.png", _gameRenderer, false);
	platformSprite = std::make_shared<Sprite>("Resources/Sprites/platform.png", _gameRenderer, false);

	objects.push_back(std::make_unique<Player>(Vector2(100.0f, 0.0f), PLAYER1));

	camera.PushTargetBack(Vector2(1200.0f, 0.0f));
	camera.PushTargetBack(Vector2(0.0f, 0.0f));
	camera.SetMoveSpeed(20.0f);

	LevelLoader::LoadLevel("Resources/Levels/LevelOne.csv", objects);

	for (auto& object : objects) {
		switch (object->GetType()) {
		case PLAYER: static_cast<Player*>(object.get())->Initialise(sceneWorld.get(), playerSprite); break;
		case PLATFORM: static_cast<Platform*>(object.get())->Initialise(sceneWorld.get(), platformSprite); break;
		}
	}
}

void SceneTest::Unload() {
}

void SceneTest::Update() {
	sceneWorld->Step(deltaTime, velIterations, posIterations);

	timeElapsed += deltaTime;

	for (auto& entity : objects) {
		switch (entity->GetType()) {
		case PLAYER: static_cast<Player*>(entity.get())->Update(&camera); break;
		case PLATFORM: static_cast<Platform*>(entity.get())->Update(&camera, timeElapsed); break;
		}
	}

	camera.Update();
}

void SceneTest::Render(SDL_Renderer* _gameRenderer) {
	textLabel->Render(_gameRenderer);
}

void SceneTest::ButtonDown(SDL_JoystickID _gamepadID, Uint8 _button) {

}

void SceneTest::ButtonUp(SDL_JoystickID _gamepadID, Uint8 _button) {

}

void SceneTest::RightTrigger(SDL_JoystickID _gamepadID, float _axisValue) {

}

void SceneTest::LeftTrigger(SDL_JoystickID gamepadID, float axisValue) {

}

void SceneTest::ControllerAdded(int deviceIndex) {
	std::cout << "Controller number " << deviceIndex << " added" << std::endl;
}
