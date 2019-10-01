#pragma once
#include "Utilities.h"
#include "Entity.h"
#include "Ball.h"

class Player : public Entity {
public:
	Player(Vector2 position, Controllers playerNum);

	void Initialise(b2World* world, std::shared_ptr<Sprite> playSprite);
	void Render(SDL_Renderer * renderer);
	void Update(Camera* gameCamera);

	void Jump();
	void FinishJump();
	void MoveHorizontal(float scale);

	void ThrowBall();

	void addCoin();
	int getCoins();

	void GainBall(Ball* ball);
	bool GetBall();

	void SetCanJump(bool newCanJump);

	Uint32 jumpTimerCallback(Uint32 interval, void* param);

	static int GetJumps();
private:
	Controllers playerIndex;

	std::unique_ptr<Collider> collider;

	Ball* storedBall;

	float width = 50.0f;
	float height = 50.0f;

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
	bool haveBall = false;
};