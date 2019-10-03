#include "RespawnPlatform.h"

//RespawnPlatform::RespawnPlatform(Vector2 _position, int _respawnNumber) : Platform(_position)
//{
//	respawnNumber = _respawnNumber;
//}

RespawnPlatform::RespawnPlatform(TileInfo info, int _respawnNumber) : Platform(info)
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
		ColliderType::RESPAWN,
		this
	};

	collider = std::make_unique<Collider>(position, info,
		Vector2(
			thisInfo.dimensions.x * width,
			thisInfo.dimensions.y * height
		));

	collider->InitialiseStatic(_world);
	collider->SetCollisionCategory(CATEGORY_PLATFORM);
	collider->SetCollisionMask(MASK_PLATFORM_COLLIDE);

	SetPosition(collider->GetPosition());
}

void RespawnPlatform::Activate()
{
	isActive = true;
	// TODO: create visual feedback to show a new checkpoint has been reached
	// TODO: respawn players
	std::cout << "ACTIVATE" << std::endl;
}