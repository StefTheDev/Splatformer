#include "Ball.h"
#include <iostream>



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

	collider->InitialiseKinematicCircle(_world, true);
	collider->SetCollisionCategory(CATEGORY_BALL);
	collider->SetCollisionMask(MASK_BALL_DEFAULT);

	SetPosition(collider->GetPosition());
}

void Ball::BindToPlayer(Vector2 _position) {

	_position.y *= -1.0f;
	this->SetPosition(_position);
	collider->body->SetTransform(position.AsBox2D(), 0.0f);
}

void Ball::Update(Camera* _gameCamera) {
	SetPosition(collider->GetPosition() - _gameCamera->GetPosition());

	GetSprite()->Play("idle");

	Entity::Update();
}

void Ball::Render(SDL_Renderer * _renderer){
	Entity::Render(_renderer);
}


void Ball::Collect() {

	collected = true;
	this->collider->body->GetFixtureList()[0].SetSensor(true);
}

bool Ball::isCollected() {

	return collected;

}

void Ball::ThrowBall(Vector2 _position, int _button) {
	// apply to ball

	thrown = true;
	collider->body->SetType(b2_dynamicBody);
	collider->body->SetActive(true);
	collider->body->SetTransform(_position.AsBox2D(), 0.0f);
	collider->body->SetLinearVelocity({ (75.0f * _button), 0.0f });
	this->collider->body->GetFixtureList()[0].SetSensor(false);
	this->collider->SetCollisionMask(MASK_BALL_NOCOLLIDE);

}

bool Ball::IsThrown() {

	return thrown;
}