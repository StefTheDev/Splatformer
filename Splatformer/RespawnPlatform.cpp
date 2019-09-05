#include "RespawnPlatform.h"

RespawnPlatform::RespawnPlatform(Vector2 _position, int _respawnNumber) : Platform(_position)
{
	respawnNumber = _respawnNumber;
}

void RespawnPlatform::Update(Camera * gameCamera, float sceneTime)
{
	Platform::Update(gameCamera, sceneTime);
	// if a player lands on this 
	// isActive = true;
}

void RespawnPlatform::Initialise(b2World * _world, std::shared_ptr<Sprite> _platformSprite)
{
	std::cout << "Initialise in RespawnChild was called" << std::endl;
	if (!LoadSprite(_platformSprite)) return;

	GetSprite()->Add("idle", SpriteAnimation{ 0, 1, 500 }); //Index, frames, speed

	DataContainer info = {
		ColliderType::PLT,
		this
	};

	collider = std::make_unique<Collider>(position, info, Vector2(width, height));

	collider->InitialiseStatic(_world);
	collider->SetCollisionCategory(CATEGORY_PLATFORM);
	collider->SetCollisionMask(MASK_PLATFORM_COLLIDE);

	SetPosition(collider->GetPosition());
}
