#pragma once
#include "scene.h"

#include "Player.h"
#include "Platform.h"
#include "Coin.h"
#include "Ball.h"
#include "RespawnPlatform.h"

//UI Entities
#include "UIButton.h"
#include "UIText.h"

class GameScene : public Scene {
public:
	GameScene();

	void Update() override;
	void Render(SDL_Renderer* gameRenderer) override;

	bool IsPaused() const;

private:
	void Load(SDL_Renderer* _gameRenderer) override;
	void Unload() override;

	void ButtonDown(SDL_JoystickID gamepadID, Uint8 button) override;
	void ButtonUp(SDL_JoystickID gamepadID, Uint8 button) override;
	void RightTrigger(SDL_JoystickID gamepadID, float axisValue) override;
	void LeftTrigger(SDL_JoystickID gamepadID, float axisValue) override;
	void ControllerAdded(int deviceIndex) override;
	void ControllerRemapped(SDL_JoystickID gamePad) override;

	//std::map<SDL_JoystickID, Player> players;
	std::unique_ptr<b2World> sceneWorld;
	PlatformingListener* contactListener;

	std::shared_ptr<Sprite> playerSprite, platformSprite, buttonSprite, coinSprite, ballSprite;

	std::vector<SDL_GameController*> controllers;

	void LoadControllers();
	// compares the number of gamepads with number of players and takes the appropriate actions
	void ControllerCheck();

	float timeElapsed;
	bool paused = false;

	std::vector<RespawnPlatform*> respawnPoints;
	RespawnPlatform* furthestActivatedPlatform = nullptr;
	RespawnPlatform* furthestActivatedPlatformPlusOne = nullptr;
	//RespawnPlatform* furthest
	int latestRespawn = -5;

	std::vector<Player*> players;
	// check if players need to be respawned
	void ProcessRespawn();
	void RespawnPlayers();

	std::unique_ptr<UIText> winText;
	std::vector<std::unique_ptr<UIText>> scores;

	bool gameOver = false;
};