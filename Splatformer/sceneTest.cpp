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

	playerSprite = std::make_shared<Sprite>("Resources/Sprites/player.png", _gameRenderer, false);
	platformSprite = std::make_shared<Sprite>("Resources/Sprites/platform.png", _gameRenderer, false);
	coinSprite = std::make_shared<Sprite>("Resources/Sprites/coin.png", _gameRenderer, false);
	ballSprite = std::make_shared<Sprite>("Resources/Sprites/coin.png", _gameRenderer, false);

	objects.push_back(std::make_unique<Player>(Vector2(50.0f, 0.0f), PLAYER1));

	camera.PushTargetBack(Vector2(1200.0f, 0.0f));
	camera.PushTargetBack(Vector2(0.0f, 0.0f));
	camera.SetMoveSpeed(100.0f);

	LevelLoader::LoadLevel("Resources/Levels/LevelOne.csv", objects);

	for (auto& object : objects) {
		switch (object->GetType()) {
		case PLAYER: static_cast<Player*>(object.get())->Initialise(sceneWorld.get(), playerSprite); break;
		case PLATFORM: static_cast<Platform*>(object.get())->Initialise(sceneWorld.get(), platformSprite); break;
		case COIN: static_cast<Coin*>(object.get())->Initialise(sceneWorld.get(), coinSprite); break;
		case BALL: static_cast<Ball*>(object.get())->Initialise(sceneWorld.get(), ballSprite); break;
		}
	}
}

void SceneTest::Unload() {
}

void SceneTest::Update() {
	sceneWorld->Step(deltaTime, velIterations, posIterations);

	timeElapsed += deltaTime;

	for (std::vector<std::unique_ptr<Entity>>::iterator entity = objects.begin(); entity != objects.end(); ++entity){
		if ((*entity)->ShouldDelete()) {
			entity = objects.erase(entity);
		}
		else {
			switch ((*entity)->GetType()) {
			case PLAYER: static_cast<Player*>((*entity).get())->Update(&camera); break;
			case PLATFORM: static_cast<Platform*>((*entity).get())->Update(&camera, timeElapsed); break;
			case COIN: static_cast<Coin*>((*entity).get())->Update(&camera); break;
			case BALL: static_cast<Coin*>((*entity).get())->Update(&camera); break;
			}
		}
	}

	camera.Update();
}

void SceneTest::Render(SDL_Renderer* _gameRenderer) {
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
