#include "GameScene.h"

#include "LevelLoader.h"
#include "GameManager.h"
#include "SpriteManager.h"
#include "Background.h"

#include <algorithm>

constexpr int velIterations = 8;
constexpr int posIterations = 3;

constexpr float cameraSpeed = 100.0f;
constexpr float maxCamMulti = 10.0f;

std::string levelNames[] = {
	"LevelOne",
	"LevelTwo",
	"LevelThree",
	"LevelFour",
	"JasonLevel",
};

GameScene::GameScene() {
	b2Vec2 gravity(0.0f, -39.2f);

	camera = new Camera(1920.0f, 1080.0f);

	contactListener = new PlatformingListener();

	sceneWorld = std::make_unique<b2World>(gravity);
	sceneWorld->SetContactListener(contactListener);
	sceneWorld->SetAllowSleeping(false);

	SoundManager::PlaySound("game bgm", FMOD_LOOP_NORMAL);
}


GameScene::~GameScene()
{
	delete camera;

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
	coinSprite = std::make_shared<Sprite>("Resources/Sprites/SugarCube.png", _gameRenderer, false);
	ballSprite = std::make_shared<Sprite>("Resources/Sprites/ball.png", _gameRenderer, false);
	backgroundSprite = std::make_shared<Sprite>("Resources/Sprites/Background.png", _gameRenderer, false);
	backgroundSprite->SetSource(Vector2(2500, 1080));

	SpriteManager::Get()->AddSprite("JumpPlatCounter", std::make_shared<Sprite>("Resources/Sprites/GemSpriteSheet.png", _gameRenderer, false));
	SpriteManager::Get()->GetSprite("JumpPlatCounter")->SetSource(Vector2(32.0f, 32.0f));

	SpriteManager::Get()->AddSprite("RespawnSprite", std::make_shared<Sprite>("Resources/Sprites/respawn.png", _gameRenderer, false));
	SpriteManager::Get()->GetSprite("RespawnSprite")->SetSource(Vector2(64.0f, 32.0f));

	SpriteManager::Get()->AddSprite("TimePlatCounter", std::make_shared<Sprite>("Resources/Sprites/TimeGemSpriteSheet.png", _gameRenderer, false));
	SpriteManager::Get()->GetSprite("TimePlatCounter")->SetSource(Vector2(32.0f, 32.0f));

	SpriteManager::Get()->AddSprite("RespawnGems", std::make_shared<Sprite>("Resources/Sprites/RespawnGems.png", _gameRenderer, false));
	SpriteManager::Get()->GetSprite("RespawnGems")->SetSource(Vector2(32.0f, 32.0f));

	SpriteManager::Get()->AddSprite("ProgressBarSprite", std::make_shared<Sprite>("Resources/Sprites/player.png", _gameRenderer, false));
	SpriteManager::Get()->GetSprite("ProgressBarSprite")->SetSource(Vector2(1900.0f, 64.0f));

	SpriteManager::Get()->AddSprite("ProgressBarFill", std::make_shared<Sprite>("Resources/Sprites/green.png", _gameRenderer, false));
	SpriteManager::Get()->GetSprite("ProgressBarFill")->SetSource(Vector2(1900.0f, 64.0f));

	SpriteManager::Get()->AddSprite("ProgressIcon", std::make_shared<Sprite>("Resources/Sprites/pointer.png", _gameRenderer, false));
	SpriteManager::Get()->GetSprite("ProgressIcon")->SetSource(Vector2(32.0f, 64.0f));

	camera->Initialise(sceneWorld.get());

	std::unique_ptr<Background> background = std::make_unique<Background>(Vector2(0.0f,0.0f));
	objects.push_back(std::move(background));

	LevelLoader::LoadLevel("Resources/Levels/"+ levelNames[SELECTED_LEVEL] +".csv", objects, respawnPoints);

	std::sort(respawnPoints.begin(), respawnPoints.end(), RespawnPlatform::sortAscending);

	LoadControllers();
	for (auto& object : objects) {
		switch (object->GetType()) {
		case PLAYER: static_cast<Player*>(object.get())->Initialise(sceneWorld.get(), playerSprite); break;
		case PLATFORM: static_cast<Platform*>(object.get())->Initialise(sceneWorld.get(), platformSprite); break;
		case COIN: static_cast<Coin*>(object.get())->Initialise(sceneWorld.get(), coinSprite); break;
		case BALL: static_cast<Ball*>(object.get())->Initialise(sceneWorld.get(), ballSprite); break;
		case BACKGROUND: static_cast<Background*>(object.get())->Initialise(sceneWorld.get(), backgroundSprite); break;
		}
	}

	respawnPoints[0]->Activate();
	// get the distanceFromBeginningToEnd
	distanceFromBeginningToEnd = (respawnPoints.front()->GetPosition() - respawnPoints.back()->GetPosition()).Magnitude();

	camera->SetPosition(respawnPoints[0]->GetPosition());
	for (auto it = respawnPoints.begin(); it != respawnPoints.end(); it++) {
		camera->PushTargetBack((*it)->GetPosition());
	}
	camera->SetMoveSpeed(cameraSpeed);

	float xScale = 0.8f;
	float xOffset = ((1920 * xScale) / (players.size() + 1)) * -0.5f;
	float stepDist = (1920 * xScale) / (players.size() + 1);

	for (int i = 0; i < players.size(); i++)
	{
		std::unique_ptr<UIText> score = std::make_unique<UIText>();
		score->LoadSprite(nullptr);
		score->Initialise(Vector2(xOffset + (i * stepDist), 400.0f), "Test", 36, SDL_Color{ 0, 0, 0 }, _gameRenderer);
		scores.push_back(std::move(score));
	}
}

void GameScene::Unload()
{
	SoundManager::loopChannel->stop();
	controllers.clear();
}

void GameScene::Update() {

	sceneWorld->Step(deltaTime, velIterations, posIterations);

	timeElapsed += deltaTime;

	float highestScalar = -99999.0f;

	if (respawnQueued && camera->Arrived()) {
		RespawnPlayers();
		respawnQueued = false;
	}

	bool allDead = true;

	for (int i = 0; i < players.size(); i++)
	{
		scores[i]->Update();
		scores[i]->SetText("Player " + std::to_string(i + 1) + ": " + std::to_string(players[i]->getCoins() - players[i]->GetDeaths()));

		if (players[i]->CheckIsAlive()) {
			allDead = false;
			Vector2 camMid = camera->GetPosition() + Vector2(camera->GetWidth()/2.0f, camera->GetHeight()/2.0f);
			Vector2 playerFromMiddle = players[i]->GetPosition() - Vector2(camera->GetWidth() / 2.0f, camera->GetHeight() / 2.0f);

			float plrCamDot = playerFromMiddle.Dot(camera->GetMoveVector());

			//Clamp
			float clampedValue = std::max(plrCamDot, 0.0f);

			float speedScalar = powf(1.02f, clampedValue/2.0f);

			highestScalar = std::max(highestScalar, speedScalar);
		}
	}

	if (highestScalar < 0) highestScalar = 1.0f;

	if(!allDead && highestScalar < 100) camera->SetMoveSpeed(cameraSpeed * highestScalar);

	if (!gameOver)
	{
		ControllerCheck();

		for (std::vector<std::unique_ptr<Entity>>::iterator entity = objects.begin(); entity != objects.end(); ++entity) {
			if ((*entity)->ShouldDelete()) {
				entity = objects.erase(entity);
			}
			else {
				switch ((*entity)->GetType()) {
				case PLAYER: static_cast<Player*>((*entity).get())->Update(camera); break;
				case PLATFORM: static_cast<Platform*>((*entity).get())->Update(camera, timeElapsed); break;
				case COIN: static_cast<Coin*>((*entity).get())->Update(camera); break;
				case BALL: static_cast<Ball*>((*entity).get())->Update(camera); break;
				}
			}
		}

		CheckClosest();
		ProcessRespawn();
		camera->Update();

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

void GameScene::Render(SDL_Renderer* _gameRenderer) 
{
	for (int i = 0; i < players.size(); i++)
	{
		scores[i]->Render(_gameRenderer);
	}

	// PROGRESS BAR
	SpriteManager::Get()->GetSprite("ProgressBarSprite")->Draw(_gameRenderer, { 10.0f, WINDOW_HEIGHT - 32.0f}, { 1900.0f, 64.0f });

	// calculate how far the players have gotten in the level
	SpriteManager::Get()->GetSprite("ProgressBarFill")->Draw(_gameRenderer, { 10.0f, WINDOW_HEIGHT - 32.0f }, { 1900.0f * progressBarScale + 20.0f, 64.0f });

	SpriteManager::Get()->GetSprite("ProgressIcon")->Draw(_gameRenderer, { 10.0f + progressBarScale*1900.0f, WINDOW_HEIGHT - 64.0f}, { 32.0f, 64.0f });


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
				RespawnPlayers();
				break;
			}
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
				return;
			}
		}

		if(!respawnQueued) RespawnCamera();
	}
}

void GameScene::RespawnCamera() {
	if (furthestActivatedPlatform != nullptr) {

		// clear the camera queue
		camera->ClearQueue();

		// send camera to the latest activated respawn platform
		// and push all the subsequent respawn platforms as well

		auto it = respawnPoints.end() - 1;
		
		do {
			camera->PushTargetFront(Vector2((*it)->GetCollider()->body.get()->GetPosition()));
			it--;
		} while (*it != furthestActivatedPlatform && it != respawnPoints.begin());

		camera->PushTargetFront(Vector2(furthestActivatedPlatform->GetCollider()->body.get()->GetPosition()));

		camera->SetMoveSpeed(1500.0f);

		respawnQueued = true;
	}
}

void GameScene::RespawnPlayers()
{
	if (furthestActivatedPlatform != nullptr)
	{
		Vector2 resPos = Vector2(furthestActivatedPlatform->GetCollider()->body.get()->GetPosition());
		resPos.y *= -1.0f;

		Vector2 spawnPosition = resPos + Vector2(0.0f, 64.0f);

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

void GameScene::CheckClosest()
{	
	float closest = INT_MAX;
	float distance;
	for (auto it = players.begin(); it != players.end(); it++)
	{
		distance = ((*it)->GetPosition() - respawnPoints.back()->GetPosition()).Magnitude();
		if (distance < closest && (*it)->CheckIsAlive())
		{
			closest = distance;
		}
	}
	currentDistance = closest;

	progressBarScale = 1 - currentDistance / distanceFromBeginningToEnd;

	progressBarScale = b2Clamp(progressBarScale, 0.0f, 1.0f);
}

