#include "JumpPlatform.h"
#include "SpriteManager.h"

JumpPlatform::JumpPlatform(TileInfo info, int _jumpsOn, int _jumpsOff) : Platform(info) {
	jumpsOn = _jumpsOn;
	jumpsOff = _jumpsOff;
}

void JumpPlatform::Update(Camera* _gameCamera, float _sceneTime) {
	Platform::Update(_gameCamera, _sceneTime);
	
	SetCanCollide((Player::GetJumps() % (jumpsOn + jumpsOff)) < jumpsOn);
}

void JumpPlatform::Render(SDL_Renderer* _renderer) {
	int currentJumps = 0, maxJumps = 0;

	if (canCollide) {
		currentJumps = jumpsOn - (Player::GetJumps() % (jumpsOn + jumpsOff));
		maxJumps = jumpsOn;
	} else {
		currentJumps = jumpsOff - ((Player::GetJumps() % (jumpsOn + jumpsOff)) - jumpsOn);
		maxJumps = jumpsOff;
	}

	GetSprite()->Draw(
		_renderer,
		position,
		Vector2(thisInfo.dimensions.x * width, thisInfo.dimensions.y * height),
		0.0f,
		0,
		static_cast<int>(!canCollide)
	);
	
	float sizeX = thisInfo.dimensions.x * width;
	float sizeY = thisInfo.dimensions.y * height;

	float halfHeight = sizeY / 2.0f;
	float halfWidth = sizeX / 2.0f;
	float xOffset = halfHeight + ((sizeX - sizeY) / (maxJumps + 1));
	float stepDist = (sizeX - sizeY) / (maxJumps + 1);

	for (int i = 0; i < currentJumps; i++) {
		SpriteManager::Get()->GetSprite("JumpPlatCounter")->Draw(
			_renderer,
			Vector2(position.x + (xOffset + (i * stepDist)) - 16, position.y + halfHeight - 16),
			Vector2(32, 32),
			0.0f,
			0,
			static_cast<int>(!canCollide)
		);
	}
}
