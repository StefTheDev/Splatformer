#include "GameScene.h"

#include "LevelLoader.h"
#include "GameManager.h"
#include "SpriteManager.h"

constexpr int velIterations = 8;
constexpr int posIterations = 3;

GameScene::GameScene() {
	b2Vec2 gravity(0.0f, -39.2f);

	camera = Camera(1920.0f, 1080.0f);

	contactListener = new PlatformingListener();

	sceneWorld = std::make_unique<b2World>(gravity);
	sceneWorld->SetContactListener(contactListener);
	sceneWorld->SetAllowSleeping(false);
}


GameScene::~GameScene()
{


	/*
	delete furthestActivatedPlatform;
	delete furthestActivatedPlatformPlusOne;
	delete contactListener;
	*/
}

void GameScene::Load(SDL_Renderer* _gameRenderer) {
	for (int i = 0; i < SDL_NumJoysticks(); ++i) {
		if (SDL_IsGameController(i)) {
			controllers.push_back(SDL_GameControllerOpen(i));
		}
	}

	playerSprite = std::make_shared<Sprite>("Resources/Sprites/Apple.png", _gameRenderer, false);
	platformSprite = std::make_shared<Sprite>("Resources/Sprites/PlatformSpriteSheet.png", _gameRenderer, false);
	platformSprite->SetSource({64.0f, 32.0f});
	coinSprite = std::make_shared<Sprite>("Resources/Sprites/Carrot.png", _gameRenderer, false);
	ballSprite = std::make_shared<Sprite>("Resources/Sprites/Onion.png", _gameRenderer, false);

	SpriteManager::Get()->AddSprite("JumpPlatCounter", std::make_shared<Sprite>("Resources/Sprites/GemSpriteSheet.png", _gameRenderer, false));
	SpriteManager::Get()->GetSprite("JumpPlatCounter")->SetSource(Vector2(32.0f, 32.0f));

	/*objects.push_back(std::make_unique<Player>(Vector2(50.0f, 0.0f), PLAYER1));
	players.push_back((Player*)objects.back().get());*/
	//objects.push_back(std::make_unique<Player>(Vector2(50.0f, 0.0f), PLAYER2));
	//players.push_back((Player*)objects.back().get());

	std::unique_ptr<UIButton> button = std::make_unique<UIButton>();
	button->LoadSprite(buttonSprite);
	button->Initialise(Vector2((-WINDOW_WIDTH/2) + 100, -500.0f), "Menu", 32, _gameRenderer, [this] {
		GameManager::GetInstance()->Switch(MENU);
	});

	objects.push_back(std::move(button));

	winText = std::make_unique<UIText>();

	winText->LoadSprite(nullptr);
	winText->Initialise(Vector2(0.0f, -500.0f), "", 64, SDL_Color{ 255, 255, 255 }, _gameRenderer);

	camera.Initialise(sceneWorld.get());

	/*camera.PushTargetBack(Vector2(1200.0f, 0.0f));
	camera.PushTargetBack(Vector2(0.0f, 0.0f));
	camera.SetMoveSpeed(100.0f);*/

	LevelLoader::LoadLevel("Resources/Levels/LevelThree.csv", objects, respawnPoints);


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


	for (int i = 0; i < players.size(); i++)
	{
		std::unique_ptr<UIText> score = std::make_unique<UIText>();
		score->LoadSprite(nullptr);
		score->Initialise(Vector2(i * 100, 400.0f), "Test", 16, SDL_Color{ 255, 255, 255 }, _gameRenderer);

		scores.push_back(std::move(score));
	}
}

void GameScene::Unload()
{

	controllers.clear();
}

void GameScene::Update() {
	sceneWorld->Step(deltaTime, velIterations, posIterations);

	timeElapsed += deltaTime;

	winText->Update();

	for (int i = 0; i < players.size(); i++)
	{
		scores[i]->Update();
		scores[i]->SetText("Player " + std::to_string(i + 1) + ": " + std::to_string(players[i]->getCoins() - players[i]->GetDeaths()));
	}

	if (!gameOver)
	{
		ControllerCheck();

		for (std::vector<std::unique_ptr<Entity>>::iterator entity = objects.begin(); entity != objects.end(); ++entity) {
			if ((*entity)->ShouldDelete()) {
				entity = objects.erase(entity);
			}
			else {
				switch ((*entity)->GetType()) {
				case PLAYER: static_cast<Player*>((*entity).get())->Update(&camera); break;
				case PLATFORM: static_cast<Platform*>((*entity).get())->Update(&camera, timeElapsed); break;
				case COIN: static_cast<Coin*>((*entity).get())->Update(&camera); break;
				case BALL: static_cast<Ball*>((*entity).get())->Update(&camera); break;
				}
			}
		}


		ProcessRespawn();
		camera.Update();

		// the final checkpoint has been reached
		if (respawnPoints.back()->GetActive())
		{
			gameOver = true;
			// check who won 
			for (int i = 0; i < players.size(); i++)
			{
				int score = players[i]->getCoins() - players[i]->GetDeaths();
				GameManager::GetInstance()->AddScore(ScoreData{i, score });
			}
			GameManager::GetInstance()->Switch(WINNING);
		}
	}
}

void GameScene::Render(SDL_Renderer* _gameRenderer) {
	winText->Render(_gameRenderer);

	for (int i = 0; i < players.size(); i++)
	{
		scores[i]->Render(_gameRenderer);
	}

}

bool GameScene::IsPaused() const
{
	return paused;
}

void GameScene::ButtonDown(SDL_JoystickID _gamepadID, Uint8 _button) {

}

void GameScene::ButtonUp(SDL_JoystickID _gamepadID, Uint8 _button) {

}

void GameScene::RightTrigger(SDL_JoystickID _gamepadID, float _axisValue) {

}

void GameScene::LeftTrigger(SDL_JoystickID gamepadID, float axisValue) {

}

void GameScene::ControllerAdded(int deviceIndex) {
	std::cout << "Controller number " << deviceIndex << " added" << std::endl;
}

void GameScene::ControllerRemapped(SDL_JoystickID _gamePad) {
	std::cout << "Controller Remapped: " << _gamePad << std::endl;
}

void GameScene::LoadControllers()
{
	for (int i = 0; i < Input::GetInstance()->GetNumGamepads(); i++)
	{

		Vector2 _test = respawnPoints[0]->GetPosition() + Vector2(0.0f, PLAYER_HEIGHT);
		objects.push_back(std::make_unique<Player>(
			_test,
			Controllers(i)));
		players.push_back((Player*)objects.back().get());
	}
}

void GameScene::ControllerCheck()
{
	if (sceneWorld == nullptr) return;
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

void GameScene::ProcessRespawn()
{
	bool needToRespawn = true;

	// find if a new platform has been activated
	for (auto it = respawnPoints.begin(); it != respawnPoints.end(); it++)
	{
		if ((*it)->GetActive())
		{
			furthestActivatedPlatform = (*it);
			auto itPlusOne = it + 1;
			// get the furthestActivatedPlatformPlusOne
			if (itPlusOne == respawnPoints.end())
			{
				furthestActivatedPlatformPlusOne = furthestActivatedPlatform;
			}
			else
			{
				furthestActivatedPlatformPlusOne = (*itPlusOne);
			}
		}
	}

	// a new RespawnPlatform has been activated
	if (furthestActivatedPlatform->respawnNumber > latestRespawn)
	{
		latestRespawn = furthestActivatedPlatform->respawnNumber;
		//check if any player is dead
		for (auto it = players.begin(); it != players.end(); it++) {
			if (!(*it)->CheckIsAlive()) {
				needToRespawn = true;
				break;
			}
			else needToRespawn = false;
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

void GameScene::RespawnPlayers()
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

	if (furthestActivatedPlatform != nullptr)
	{
		// send camera to the platform
		if (camera.IsQueueEmpty())
		{
			auto it = respawnPoints.end() - 1;
			while (*it != furthestActivatedPlatformPlusOne)
			{
				camera.PushTargetFront(Vector2((*it)->GetCollider()->body.get()->GetPosition()));
				it--;
			}
		}
		camera.PushTargetFront(Vector2(furthestActivatedPlatform->GetCollider()->body.get()->GetPosition()));
		camera.SetMoveSpeed(500.0f);
		//camera.SetPosition(Vector2(furthestPlatform->GetCollider()->body.get()->GetPosition()));

		Vector2 spawnPosition = Vector2(furthestActivatedPlatform->GetCollider()->body.get()->GetPosition()) - Vector2(0.0f, camera.GetHeight() / 2.0f);
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
