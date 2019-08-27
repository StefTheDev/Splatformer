#pragma once
#include "Utilities.h"
#include "Entity.h"

class Player : public Entity {
public:
	Player();

	void Initialise(Vector2 position, b2World* world, std::shared_ptr<Sprite> playSprite);
	void Update(Camera* _gameCamera);

	void Jump();

private:
	std::unique_ptr<Collider> collider;

	float width = 50.0f;
	float height = 50.0f;
};