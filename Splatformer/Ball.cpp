#include "Ball.h"



Ball::Ball(Vector2 _position)
{
	type = BALL;

	_position.y *= -1.0f;

	_position.x *= width;
	_position.y *= height;

	Entity::Initialise(_position, { width, height });
}

void Ball::Initialise(b2World* _world, std::shared_ptr<Sprite> _ballSprite) {
	if (!LoadSprite(_ballSprite)) return;

	GetSprite()->Add("idle", SpriteAnimation{ 0, 1, 500 }); //Index, frames, speed

	DataContainer info = {
		ColliderType::CBALL,
		this
	};

	collider = std::make_unique<Collider>(position, info, Vector2(width, height));

	collider->InitialiseStatic(_world, true);
	collider->SetCollisionCategory(CATEGORY_BALL);
	collider->SetCollisionMask(MASK_BALL_DEFAULT);

	SetPosition(collider->GetPosition());
}

void Ball::Update(Camera* _gameCamera) {
	SetPosition(collider->GetPosition() - _gameCamera->GetPosition());

	GetSprite()->Play("idle");

	Entity::Update();
}


void Ball::Collected() {

	shouldDelete = true;

}