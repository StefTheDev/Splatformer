#pragma once
#include "Platform.h"

class TimePlatform : public Platform {
public:
	TimePlatform(TileInfo info, float timeOn, float timeOff);

	void Update(Camera* gameCamera, float sceneTime) override;
	void Render(SDL_Renderer* renderer) override;

private:
	float currentTime = 0.0f;
	float timeOn = 0.0f;
	float timeOff = 0.0f;

	std::shared_ptr<Sprite> toggleSprite;
	std::shared_ptr<Sprite> countSprite;
};