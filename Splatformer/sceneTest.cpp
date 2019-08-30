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

	objects.push_back(std::make_unique<Player>(Vector2(50.0f, 0.0f)));

	camera.SetTargetPosition(Vector2(1200.0f, 0.0f));
	camera.SetMoveSpeed(100.0f);

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
	//camera.Update();

	if (Input::GetInstance()->IsControllerButtonPressed(PLAYER1, SDL_CONTROLLER_BUTTON_A)) {
		static_cast<Player*>(objects[0].get())->Jump();
		
	} else if (!(Input::GetInstance()->IsControllerButtonHeld(PLAYER1, SDL_CONTROLLER_BUTTON_A))) {
		static_cast<Player*>(objects[0].get())->FinishJump();
	}
}

void SceneTest::Render(SDL_Renderer* _gameRenderer) {
}

void SceneTest::ButtonDown(SDL_JoystickID _gamepadID, Uint8 _button) {
	////if (_button == SDL_CONTROLLER_BUTTON_A) {
	//if (Input::GetInstance()->IsControllerButtonPressed(PLAYER1, SDL_CONTROLLER_BUTTON_A)) {

	//	static_cast<Player*>(objects[0].get())->Jump();
	//}
	//} else if (_button == SDL_CONTROLLER_BUTTON_B) {
	//static_cast<Player*>(objects[0].get())->Jump();
	//}
}

void SceneTest::ButtonUp(SDL_JoystickID _gamepadID, Uint8 _button) {
	/*if (_button == SDL_CONTROLLER_BUTTON_A) {
		static_cast<Player*>(objects[0].get())->FinishJump();
	}*/
	//static_cast<Player*>(objects[0].get())->FinishJump();
}

void SceneTest::RightTrigger(SDL_JoystickID _gamepadID, float _axisValue) {
	static_cast<Player*>(objects[0].get())->MoveRight();
}

void SceneTest::LeftTrigger(SDL_JoystickID gamepadID, float axisValue) {
	static_cast<Player*>(objects[0].get())->MoveLeft();
}

void SceneTest::ControllerAdded(int deviceIndex) {
	std::cout << "Controller number " << deviceIndex << " added" << std::endl;
}
