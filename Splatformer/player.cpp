#include "player.h"

Player::Player() {
	collider = std::make_unique<Collider>(Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f));
}

void Player::Initialise(Vector2 _position, b2World* _world, std::shared_ptr<Sprite> _playerSprite) {
	Entity::Initialise(_position, {100.0f, 100.0f});
	LoadSprite(_playerSprite);

	collider->InitialiseDynamic(_world, 1.0f, 0.3f, 0.5f);

	SetPosition(collider->GetPosition());
}

void Player::Update(Camera* _gameCamera) {
	//SetPosition(collider->GetPosition() - _gameCamera->GetPosition());

	Entity::Update();
	Transform({0.1f, 0.1f});
	//std::cout << position.x << std::endl;
}