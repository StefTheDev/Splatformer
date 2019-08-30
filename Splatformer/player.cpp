#include "player.h"

Uint32 resetGravScale(Uint32 _interval, void* _param) {
	b2Body* body = static_cast<b2Body*>(_param);

	body->SetGravityScale(1.0f);

	return 0;
}

Player::Player(Vector2 _position) {
	type = PLAYER;

	Entity::Initialise(_position, { width, height });
}

void Player::Initialise(b2World* _world, std::shared_ptr<Sprite> _playerSprite) {
	if (!LoadSprite(_playerSprite)) return;

	GetSprite()->Add("idle", SpriteAnimation{ 0, 1, 500 }); //Index, frames, speed

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

void Player::Update(Camera* _gameCamera) {
	SetPosition(collider->GetPosition() - _gameCamera->GetPosition());

	jumpedInAir = (jumpedInAir && !canJump);

	GetSprite()->Play("idle");
	Entity::Update();
}

void Player::Jump() {
	if (canJump || !jumpedInAir) {
		collider->body->SetGravityScale(0.4f);
		if (!canJump) {
			jumpedInAir = true;
			collider->body->SetLinearVelocity({ 0.0f, airJumpForce });
			jumpTimer = SDL_AddTimer(maxAirJumpTime, resetGravScale, static_cast<void*>(collider->body.get()));
		}else{
			collider->body->SetLinearVelocity({ 0.0f, jumpForce });
			jumpTimer = SDL_AddTimer(maxJumpTime, resetGravScale, static_cast<void*>(collider->body.get()));
		}
	}
}

void Player::FinishJump() {
	SDL_RemoveTimer(jumpTimer);

	collider->body->SetGravityScale(1.0f);
}

void Player::MoveRight() {
	collider->body->ApplyLinearImpulseToCenter({ 1.0f, 0.0f }, true);
}

void Player::MoveLeft() {
	collider->body->ApplyLinearImpulseToCenter({ -1.0f, 0.0f }, true);
}

void Player::SetCanJump(bool _newCanJump) {
	canJump = _newCanJump;
}

Uint32 Player::jumpTimerCallback(Uint32 interval, void* param) {
	collider->body->SetGravityScale(1.0f);

	return 0;
}
