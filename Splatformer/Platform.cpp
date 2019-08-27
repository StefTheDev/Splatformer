#include "Platform.h"

Platform::Platform() {
}

void Platform::Initialise(Vector2 _position, b2World* _world, std::shared_ptr<Sprite> _platformSprite) {
	if (!LoadSprite(_platformSprite)) return;

	GetSprite()->Add("idle", SpriteAnimation{ 0, 1, 500 }); //Index, frames, speed

	Entity::Initialise(_position, { width, height });

	collider = std::make_unique<Collider>(_position, Vector2(width, height));
	
	collider->InitialiseStatic(_world);
	collider->SetCollisionCategory(CATEGORY_PLATFORM);
	collider->SetCollisionMask(MASK_PLATFORM_COLLIDE);

	SetPosition(collider->GetPosition());
}

void Platform::Update(Camera* _gameCamera) {
	SetPosition(collider->GetPosition() - _gameCamera->GetPosition());

	GetSprite()->Play("idle");
	Entity::Update();
}

void Platform::SetCanCollide(bool _canCollide) {
	canCollide = _canCollide;

	collider->SetCollisionMask(canCollide ? MASK_PLATFORM_COLLIDE : MASK_PLATFORM_NOCOLLIDE);
}

bool Platform::CanCollide() {
	return canCollide;
}
