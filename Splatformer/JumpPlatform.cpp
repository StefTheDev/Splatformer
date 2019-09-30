#include "JumpPlatform.h"

JumpPlatform::JumpPlatform(TileInfo info, int _jumpsOn, int _jumpsOff) : Platform(info) {
	jumpsOn = _jumpsOn;
	jumpsOff = _jumpsOff;
}

void JumpPlatform::Update(Camera* _gameCamera, float _sceneTime) {
	Platform::Update(_gameCamera, _sceneTime);
	
	SetCanCollide((Player::GetJumps() % (jumpsOn + jumpsOff)) < jumpsOn);
}
