#pragma once
#include "Utilities.h"
#include "Entity.h"


class Ball : public Entity{

public:
	Ball(Vector2 position);
	
	void Initialise(b2World* world, std::shared_ptr<Sprite> coinSprite);
	void Update(Camera* _gameCamera);

	void Collected();

private:
	std::unique_ptr<Collider> collider;

	float width = 75.0f;
	float height = 40.0f;
};