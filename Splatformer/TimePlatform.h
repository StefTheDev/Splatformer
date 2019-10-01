#pragma once
#include "Platform.h"

class TimePlatform : public Platform {
public:
	TimePlatform(TileInfo info, float timeOn, float timeOff);

	void Update(Camera* gameCamera, float sceneTime) override;

private:
	float timeOn = 0.0f;
	float timeOff = 0.0f;
};