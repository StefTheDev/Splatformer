#include "player.h"
#include "SoundManager.h"

int Player::currentJumps = 0;

Uint32 resetGravScale(Uint32 _interval, void* _param) {
	b2Body* body = static_cast<b2Body*>(_param);

	body->SetGravityScale(1.0f);

	return 0;
}

Player::Player(Vector2 _position, Controllers _playerNum) {
	type = PLAYER;
	playerIndex = _playerNum;

	Entity::Initialise(_position, { width, height });
}

void Player::Initialise(b2World* _world, std::shared_ptr<Sprite> _playerSprite) {
	if (!LoadSprite(_playerSprite)) return;

	GetSprite()->Add("idle", SpriteAnimation{ 0, 1, 500 }
	); //Index, frames, speed

	DataContainer info = {
		ColliderType::PLR, 
		this
	};

	collider = std::make_unique<Collider>(position, info, Vector2(width, height));

	collider->InitialiseDynamic(_world, 1.0f, 0.3f, 0.5f);
	collider->SetCollisionCategory(CATEGORY_PLAYER);
	collider->SetCollisionMask(MASK_PLAYER_DEFAULT);

	SetPosition(collider->GetPosition());
}

void Player::Render(SDL_Renderer * _renderer){
	//if(storedBall != nullptr) storedBall->Render(_renderer);
	Entity::Render(_renderer);
}

void Player::Update(Camera* _gameCamera) {
	if (isDead) return;

	if (Input::GetInstance()->IsControllerButtonPressed(playerIndex, SDL_CONTROLLER_BUTTON_A)) {
		Jump();

	} else if (!(Input::GetInstance()->IsControllerButtonHeld(playerIndex, SDL_CONTROLLER_BUTTON_A))) {
		FinishJump();
	}
	if (Input::GetInstance()->IsControllerButtonPressed(playerIndex, SDL_CONTROLLER_BUTTON_LEFTSHOULDER)) {
		ThrowBall(-1);
	}
	if (Input::GetInstance()->IsControllerButtonPressed(playerIndex, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER)) {
		ThrowBall(1);
	}

	float stickPos = Input::GetInstance()->GetControllerAxis(playerIndex, SDL_CONTROLLER_AXIS_LEFTX);

	if (abs(stickPos) > 0.3f) {
		MoveHorizontal(stickPos);
	}

	SetPosition(collider->GetPosition() - _gameCamera->GetPosition());

	if (storedBall != nullptr) {
		storedBall->BindToPlayer(collider->GetPosition());
	}


	jumpedInAir = (jumpedInAir && !canJump);

	GetSprite()->Play("idle");
	Entity::Update();
}

void Player::addCoin() {

	coinsCollected += 1;

}

int Player::getCoins() {

	return coinsCollected;
}

void Player::Jump() {
	if (canJump || !jumpedInAir) {
		collider->body->SetGravityScale(0.4f);
		if (!canJump) {
			jumpedInAir = true;
			collider->body->SetLinearVelocity({ collider->body->GetLinearVelocity().x, airJumpForce });
			jumpTimer = SDL_AddTimer(maxAirJumpTime, resetGravScale, static_cast<void*>(collider->body.get()));
			SoundManager::PlaySound("Jump");
		}else{
			collider->body->SetLinearVelocity({ collider->body->GetLinearVelocity().x, jumpForce });
			jumpTimer = SDL_AddTimer(maxJumpTime, resetGravScale, static_cast<void*>(collider->body.get()));
			SoundManager::PlaySound("Jump");
		}
		//Increment global jump count
		currentJumps++;
	}
}

void Player::ThrowBall(int _button) {

	//Vector2{ 960.0f, -540.0 }

	if (haveBall) {
		storedBall->ThrowBall(Vector2{collider->GetPosition().x + (55.0f * _button), -collider->GetPosition().y }, _button); //position);
		storedBall = nullptr;
		haveBall = false;
	}

}

void Player::FinishJump() {
	SDL_RemoveTimer(jumpTimer);

	collider->body->SetGravityScale(1.0f);
}

void Player::MoveHorizontal(float _scale) {
	float xVel = collider->body->GetLinearVelocity().x;

	//Signs of movement and joystick are different
	if (((_scale > 0) - (0 > _scale)) != ((xVel > 0) - (0 > xVel))) {
		collider->body->SetLinearVelocity({ collider->body->GetLinearVelocity().x/2.0f, collider->body->GetLinearVelocity().y });
	}

	collider->body->ApplyLinearImpulseToCenter({ _scale * (1 - (xVel/maxSpeed)) * incrementSpeed * deltaTime, 0.0f }, true);
}

void Player::SetCanJump(bool _newCanJump) {
	canJump = _newCanJump;
}

void Player::Kill() {
	isDead = true;

	SDL_RemoveTimer(jumpTimer);
	collider->body->SetGravityScale(0.0f);
	deaths++;

	std::cout << "Player Am Dead\n";
}

void Player::Respawn(Vector2 _respawnPosition) {
	isDead = false;

	collider->body->SetGravityScale(1.0f);
	collider->body->SetTransform((_respawnPosition).AsBox2D(), 0.0f);
	collider->body->SetLinearVelocity({ 0,0 });
	std::cout << "RESPAWN" << std::endl;
}

Uint32 Player::jumpTimerCallback(Uint32 interval, void* param) {
	collider->body->SetGravityScale(1.0f);

	return 0;
}

int Player::GetJumps() {
	return currentJumps;
}

void Player::GainBall(Ball* _ball) {
	haveBall = true;
	storedBall = _ball;
}

bool Player::GetBall() {
	return haveBall;
}