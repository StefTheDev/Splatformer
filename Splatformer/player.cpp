#include "player.h"

Player::Player() {

}

void Player::Initialise(Vector2 _position, b2World* _world, std::shared_ptr<Sprite> _playerSprite) {
	if (!LoadSprite(_playerSprite)) return;

	GetSprite()->Add("idle", SpriteAnimation{ 0, 1, 500 }); //Index, frames, speed

	Entity::Initialise(_position, { width, height });

	collider = std::make_unique<Collider>(_position, Vector2(width, height));

	collider->InitialiseDynamic(_world, 1.0f, 0.3f, 0.5f);
	collider->SetCollisionCategory(CATEGORY_PLAYER);
	collider->SetCollisionMask(MASK_PLAYER_DEFAULT);

	SetPosition(collider->GetPosition());
}

void Player::Update(Camera* _gameCamera) {
	SetPosition(collider->GetPosition() - _gameCamera->GetPosition());

	GetSprite()->Play("idle");
	Entity::Update();
	//std::cout << position.x << std::endl;
}

void Player::Jump() {
	collider->body->ApplyLinearImpulseToCenter({ 0.0f, 200.0f }, true);
	std::cout << "Jump" << std::endl;
}
