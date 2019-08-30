#include "player.h"

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

	collider->body->SetAwake(true);

	GetSprite()->Play("idle");
	Entity::Update();
}

void Player::Jump() {
	collider->body->ApplyLinearImpulseToCenter({ 0.0f, 20.0f }, true);
	std::cout << "Jump" << std::endl;
}

void Player::MoveRight() {
	collider->body->ApplyLinearImpulseToCenter({ 1.0f, 0.0f }, true);
}

void Player::MoveLeft() {
	collider->body->ApplyLinearImpulseToCenter({ -1.0f, 0.0f }, true);
}
