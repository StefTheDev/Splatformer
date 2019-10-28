#include "TimePlatform.h"
#include "SpriteManager.h"

TimePlatform::TimePlatform(TileInfo _info, float _timeOn, float _timeOff) : Platform(_info) {
	timeOn = _timeOn;
	timeOff = _timeOff;
}

void TimePlatform::Update(Camera* _gameCamera, float _sceneTime) {
	Platform::Update(_gameCamera, _sceneTime);

	SetCanCollide(fmod(_sceneTime, (timeOn + timeOff)) < timeOn);

	currentTime = _sceneTime;
}

void TimePlatform::Render(SDL_Renderer* _renderer) {
	float currTime = 0, maxTime = 0;

	if (canCollide) {
		currTime = (timeOn - fmod(currentTime, (timeOn + timeOff))) * 10.0f;
		maxTime = timeOn * 10.0f;
	} else {
		currTime = (timeOff - (fmod(currentTime, (timeOn + timeOff)) - timeOn)) * 10.0f;
		maxTime = timeOff * 10.0f;
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
	float xOffset = halfHeight + ((sizeX - sizeY) / (maxTime + 1));
	float stepDist = (sizeX - sizeY) / (maxTime + 1);

	for (int i = 0; i < static_cast<int>(ceilf(currTime)); i++) {
		int frame = 0;

		if (i == 0) frame = 1;
		else if (i == static_cast<int>(ceilf(currTime))) frame = 2;

		SpriteManager::Get()->GetSprite("TimePlatCounter")->Draw(
			_renderer,
			Vector2(position.x + (xOffset + (i * stepDist)) - 16, position.y + halfHeight - 16),
			Vector2(32, 32),
			0.0f,
			frame,
			static_cast<int>(!canCollide)
		);
	}
}
