#pragma once
#include "Utilities.h"
#include "Entity.h"

class Player : public Entity {
public:
	Player(Vector2 position);

	void Initialise(b2World* world, std::shared_ptr<Sprite> playSprite);
	void Update(Camera* _gameCamera);

	void Jump();
	void MoveRight();
	void MoveLeft();

private:
	std::unique_ptr<Collider> collider;

	float width = 50.0f;
	float height = 50.0f;
};