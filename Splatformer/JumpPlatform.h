#pragma once
#include "Platform.h"
#include "Player.h"

class JumpPlatform : public Platform{
public:
	JumpPlatform(TileInfo info, int jumpsOn, int jumpsOff);

	void Update(Camera* gameCamera, float sceneTime) override;
	void Render(SDL_Renderer* renderer) override;

private:
	int jumpsOn = 0;
	int jumpsOff = 0;

	std::shared_ptr<Sprite> toggleSprite;
	std::shared_ptr<Sprite> countSprite;
};