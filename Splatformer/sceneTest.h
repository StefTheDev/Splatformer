#pragma once
#include "scene.h"

#include "Player.h"
#include "Platform.h"
#include "Coin.h"
#include "RespawnPlatform.h"
#include "UIButton.h"

class SceneTest : public Scene {
public:
	SceneTest();

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

	std::shared_ptr<Sprite> playerSprite, platformSprite, buttonSprite, coinSprite;

	std::vector<SDL_GameController*> controllers;

	float timeElapsed;
	bool paused = false;

	std::vector<RespawnPlatform*> respawnPoints;

	std::vector<Player*> players;
	// check if players need to be respawned
	void ProcessRespawn();
	void RespawnPlayers();
};