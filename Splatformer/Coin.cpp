#include "Coin.h"


Coin::Coin(Vector2 _position){
	type = COIN;

	_position.y *= -1.0f;

	_position.x *= width;
	_position.y *= height;

	Entity::Initialise(_position, { width, height });
}

void Coin::Initialise(b2World* _world, std::shared_ptr<Sprite> _coinSprite) {
	if (!LoadSprite(_coinSprite)) return;

	GetSprite()->Add("idle", SpriteAnimation{ 0, 1, 500 }); //Index, frames, speed

	DataContainer info = {
		ColliderType::ECOIN,
		this
	};

	collider = std::make_unique<Collider>(position, info, Vector2(width, height));

	collider->InitialiseStatic(_world, true);
	collider->SetCollisionCategory(CATEGORY_COIN);
	collider->SetCollisionMask(MASK_COIN_DEFAULT);

	SetPosition(collider->GetPosition());
}

void Coin::Update(Camera* _gameCamera) {
	SetPosition(collider->GetPosition() - _gameCamera->GetPosition());

	GetSprite()->Play("idle");

	Entity::Update();
}


void Coin::Collected() {
	
	shouldDelete = true;
}