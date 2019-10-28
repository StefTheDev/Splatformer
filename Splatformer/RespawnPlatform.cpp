#include "RespawnPlatform.h"
#include "soundmanager.h"
#include "SpriteManager.h"

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

void RespawnPlatform::Render(SDL_Renderer* _renderer) {
	GetSprite()->Draw(
		_renderer,
		position,
		Vector2(thisInfo.dimensions.x * width, thisInfo.dimensions.y * height),
		0.0f,
		0,
		0
	);

	float sizeX = thisInfo.dimensions.x * width;
	float sizeY = thisInfo.dimensions.y * height;

	float halfHeight = sizeY / 2.0f;
	float halfWidth = sizeX / 2.0f;
	float xOffset = halfHeight + ((sizeX - sizeY) / 2.0f);

	SpriteManager::Get()->GetSprite("RespawnGems")->Draw(
		_renderer,
		Vector2(position.x + xOffset - 16, position.y + halfHeight - 16),
		Vector2(32, 32),
		0.0f,
		static_cast<int>(isActive),
		0
	);
}

void RespawnPlatform::Initialise(b2World * _world, std::shared_ptr<Sprite> _platformSprite)
{
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
	if (!isActive)
	{
		isActive = true;

		SoundManager::PlaySound("checkpoint reached", FMOD_DEFAULT);
		// TODO: create visual feedback to show a new checkpoint has been reached
		// TODO: respawn players
	}
}