#pragma once
#include "Utilities.h"
#include "Entity.h"

class Player : public Entity {
public:
	Player();

	void Initialise(Vector2 position, b2World* world, std::shared_ptr<Sprite> playerSprite);
	void Update(Camera* _gameCamera);

private:
	std::unique_ptr<Collider> collider;
};