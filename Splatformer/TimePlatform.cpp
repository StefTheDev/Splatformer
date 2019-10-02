#include "TimePlatform.h"

TimePlatform::TimePlatform(TileInfo _info, float _timeOn, float _timeOff) : Platform(_info) {
	timeOn = _timeOn;
	timeOff = _timeOff;
}

void TimePlatform::Update(Camera* _gameCamera, float _sceneTime) {
	Platform::Update(_gameCamera, _sceneTime);

	SetCanCollide(fmod(_sceneTime, (timeOn + timeOff)) < timeOn);

}
