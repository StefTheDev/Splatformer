#include "Platform.h"

Platform::Platform(TileInfo _info) {
	type = PLATFORM;
	thisInfo = _info;

	_info.position.y *= -1.0f;

	_info.position.x *= width;
	_info.position.y *= height;

	Entity::Initialise(_info.position, { thisInfo.dimensions.x * width, thisInfo.dimensions.y * height });
}

void Platform::Initialise(b2World* _world, std::shared_ptr<Sprite> _platformSprite) {
	std::cout << "Platform Init Called\n";
	if (!LoadSprite(_platformSprite)) std::cout << "ERROR: Couldn't load sprite\n";

	GetSprite()->Add("idle", SpriteAnimation{ 0, 1, 500 }); //Index, frames, speed

	DataContainer info = {
		ColliderType::PLT,
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

void Platform::Update(Camera* _gameCamera, float _sceneTime) {
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
