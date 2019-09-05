#pragma once
#include "Platform.h"
#include "Player.h"

class JumpPlatform : public Platform{
public:
	JumpPlatform(Vector2 _position, int jumpsOn, int jumpsOff);

	void Update(Camera* gameCamera, float sceneTime) override;

private:
	int jumpsOn = 0;
	int jumpsOff = 0;
};