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
	std::cout << "Base Platform initialised\n";

	if (!LoadSprite(_platformSprite)) std::cout << "ERROR: Couldn't load sprite\n";

	GetSprite()->Add("solid", SpriteAnimation{ 0, 1, 500 }); //Index, frames, speed
	GetSprite()->Add("notSolid", SpriteAnimation{ 1, 1, 500 }); //Index, frames, speed

	GetSprite()->Play("solid");

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

	Entity::Update();
}

void Platform::Render(SDL_Renderer* _renderer) {
	GetSprite()->Draw(
		_renderer,
		position,
		Vector2(thisInfo.dimensions.x * width, thisInfo.dimensions.y * height),
		0.0f,
		0,
		0
	);
}

void Platform::SetCanCollide(bool _canCollide) {
	canCollide = _canCollide;

	collider->SetCollisionMask(canCollide ? MASK_PLATFORM_COLLIDE : MASK_PLATFORM_NOCOLLIDE);
}

bool Platform::CanCollide() {
	return canCollide;
}
