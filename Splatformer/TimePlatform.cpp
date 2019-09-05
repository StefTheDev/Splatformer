#include "TimePlatform.h"

TimePlatform::TimePlatform(Vector2 _position, float _timeOn, float _timeOff) : Platform(_position) {
	timeOn = _timeOn;
	timeOff = _timeOff;
}

void TimePlatform::Update(Camera* _gameCamera, float _sceneTime) {
	Platform::Update(_gameCamera, _sceneTime);

	SetCanCollide(fmod(_sceneTime, (timeOn + timeOff)) < timeOn);
}
