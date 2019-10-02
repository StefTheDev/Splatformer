#pragma once
#include "Utilities.h"
#include "Entity.h"

class Player : public Entity {
public:
	Player(Vector2 position, Controllers playerNum);

	void Initialise(b2World* world, std::shared_ptr<Sprite> playSprite);
	void Update(Camera* _gameCamera);

	void Jump();
	void FinishJump();
	void MoveHorizontal(float scale);

	void addCoin();
	int getCoins();

	void SetCanJump(bool newCanJump);

	void Kill();
	void Respawn(Vector2 respawnPosition);

	bool CheckIsAlive() { return !isDead; }

	static int GetJumps();
private:
	Uint32 jumpTimerCallback(Uint32 interval, void* param);

	Controllers playerIndex;

	std::unique_ptr<Collider> collider;

	float width = 50.0f;
	float height = 50.0f;

	bool isDead = false;

	//Jumping variables
	bool canJump = false;
	bool jumpedInAir = false;
	
	//The amount of time in ms that a player can be travelling upwards for
	Uint32 maxJumpTime = 600;
	Uint32 maxAirJumpTime = 400;

	float jumpForce = 16.0f;
	float airJumpForce = 12.0f;

	//Running variables
	float incrementSpeed = 96.0f;
	float maxSpeed = 64.0f;

	SDL_TimerID jumpTimer;

	static int currentJumps;

	int coinsCollected = 0;
};