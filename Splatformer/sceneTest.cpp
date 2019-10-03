#include "sceneTest.h"

#include "LevelLoader.h"

constexpr int velIterations = 8;
constexpr int posIterations = 3;

SceneTest::SceneTest() {
	b2Vec2 gravity(0.0f, -39.2f);

	camera = Camera(1920.0f, 1080.0f);

	contactListener = new PlatformingListener();

	sceneWorld = std::make_unique<b2World>(gravity);
	sceneWorld->SetContactListener(contactListener);
	sceneWorld->SetAllowSleeping(false);
}

void SceneTest::Load(SDL_Renderer* _gameRenderer) {
	for (int i = 0; i < SDL_NumJoysticks(); ++i) {
		if (SDL_IsGameController(i)) {
			controllers.push_back(SDL_GameControllerOpen(i));
		}
	}

	playerSprite = std::make_shared<Sprite>("Resources/Sprites/Apple.png", _gameRenderer, false);
	platformSprite = std::make_shared<Sprite>("Resources/Sprites/platform_base.png", _gameRenderer, false);
	coinSprite = std::make_shared<Sprite>("Resources/Sprites/Carrot.png", _gameRenderer, false);
	ballSprite = std::make_shared<Sprite>("Resources/Sprites/Onion.png", _gameRenderer, false);
	buttonSprite = std::make_shared<Sprite>("Resources/Sprites/player.png", _gameRenderer, false);


	/*objects.push_back(std::make_unique<Player>(Vector2(50.0f, 0.0f), PLAYER1));
	players.push_back((Player*)objects.back().get());*/
	//objects.push_back(std::make_unique<Player>(Vector2(50.0f, 0.0f), PLAYER2));
	//players.push_back((Player*)objects.back().get());
	
	std::unique_ptr<UIButton> button = std::make_unique<UIButton>();
	button->LoadSprite(buttonSprite);
	button->Initialise(Vector2(0.0f, 500.0f), "Menu", 32, _gameRenderer, [this] {
		SDL_Delay(75);
	});

	objects.push_back(std::move(button));

	camera.Initialise(sceneWorld.get());

	/*camera.PushTargetBack(Vector2(1200.0f, 0.0f));
	camera.PushTargetBack(Vector2(0.0f, 0.0f));
	camera.SetMoveSpeed(100.0f);*/

	LevelLoader::LoadLevel("Resources/Levels/LevelTwo.csv", objects, respawnPoints);



	std::sort(respawnPoints.begin(), respawnPoints.end(), RespawnPlatform::sortAscending);

	

	LoadControllers();
	for (auto& object : objects) {
		switch (object->GetType()) {
		case PLAYER: static_cast<Player*>(object.get())->Initialise(sceneWorld.get(), playerSprite); break;
		case PLATFORM: static_cast<Platform*>(object.get())->Initialise(sceneWorld.get(), platformSprite); break;
		case COIN: static_cast<Coin*>(object.get())->Initialise(sceneWorld.get(), coinSprite); break;
		case BALL: static_cast<Ball*>(object.get())->Initialise(sceneWorld.get(), ballSprite); break;
		}
	}

	respawnPoints[0]->Activate();

	camera.SetPosition(respawnPoints[0]->GetPosition());
	for (auto it = respawnPoints.begin(); it != respawnPoints.end(); it++) {
		camera.PushTargetBack((*it)->GetPosition());
	}
	camera.SetMoveSpeed(100.0f);
}

void SceneTest::Unload() {
}

void SceneTest::Update() {
	sceneWorld->Step(deltaTime, velIterations, posIterations);

	timeElapsed += deltaTime;

	ControllerCheck();

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
	ProcessRespawn();
	camera.Update();
	


}

void SceneTest::Render(SDL_Renderer* _gameRenderer) {
}

bool SceneTest::IsPaused() const
{
	return paused;
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

void SceneTest::ControllerRemapped(SDL_JoystickID _gamePad) {
	std::cout << "Controller Remapped: " << _gamePad << std::endl;
}

void SceneTest::LoadControllers()
{
	for (int i = 0; i < Input::GetInstance()->GetNumGamepads(); i++)
	{

		Vector2 _test = respawnPoints[0]->GetPosition() + Vector2(0.0f, PLAYER_HEIGHT);
		objects.push_back(std::make_unique<Player>(
			_test , 
			Controllers(i)));
		players.push_back((Player*)objects.back().get());
	}
}

void SceneTest::ControllerCheck()
{
	// TODO: Incomplete. Either move to lobby scene or scrap since we are no longer adding players while the game is running
	if (Input::GetInstance()->GetNumGamepads() > players.size())
	{
		// add new players
		for (int i = players.size(); i < Input::GetInstance()->GetNumGamepads(); i++)
		{
			objects.push_back(std::make_unique<Player>(Vector2(50.0f, 0.0f), Controllers(i)));
			players.push_back((Player*)objects.back().get());
			players.back()->Initialise(sceneWorld.get(), playerSprite);
		}
	}
}

void SceneTest::ProcessRespawn()
{
	bool needToRespawn = true;
	
	// find if a new platform has been activated
	for (auto it = respawnPoints.begin(); it != respawnPoints.end(); it++)
	{
		if ((*it)->GetActive())
		{
			furthestPlatform = (*it);
		}
	}

	// a new RespawnPlatform has been activated
	if (furthestPlatform->respawnNumber > latestRespawn)
	{
		latestRespawn = furthestPlatform->respawnNumber;
		//check if any player is dead
		for (auto it = players.begin(); it != players.end(); it++) {
			if (!(*it)->CheckIsAlive()) {
				needToRespawn = true;
				break;
			} else needToRespawn = false;
		}
	}
	// have NOT reached a new checkpoint yet
	else 
	{
		// check if all players are dead
		for (auto it = players.begin(); it != players.end(); it++)
		{
			// if any player is alive
			if ((*it)->CheckIsAlive())
			{
				needToRespawn = false;
				break;
			}
		}
	}

	if (needToRespawn)
	{
		RespawnPlayers();
	}
}

void SceneTest::RespawnPlayers()
{
	//RespawnPlatform* furthestPlatform = nullptr;

	//// find which respawnPlatform to respawn on
	//for (auto it = respawnPoints.begin(); it != respawnPoints.end(); it++)
	//{
	//	if ((*it)->GetActive())
	//	{
	//		furthestPlatform = (*it);
	//	}
	//	else break;
	//}

	if (furthestPlatform != nullptr)
	{
		// send camera to the platform
		camera.PushTargetFront(Vector2(furthestPlatform->GetCollider()->body.get()->GetPosition()));
		camera.SetMoveSpeed(500.0f);
		//camera.SetPosition(Vector2(furthestPlatform->GetCollider()->body.get()->GetPosition()));

		Vector2 spawnPosition = Vector2(furthestPlatform->GetCollider()->body.get()->GetPosition()) - Vector2(0.0f, camera.GetHeight()/2.0f);
		spawnPosition.y += 32.0f;

		// respawn players
		for (auto it = players.begin(); it != players.end(); it++)
		{
			if (!(*it)->CheckIsAlive())
			{
				(*it)->Respawn(spawnPosition);
			
			}
		}
	}
}
