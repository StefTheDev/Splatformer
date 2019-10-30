#pragma once
#include "Utilities.h"
#include "Entity.h"

class Coin : public Entity
{
public:
	Coin(Vector2 position);

	void Initialise(b2World* world, std::shared_ptr<Sprite> coinSprite);
	void Update(Camera* _gameCamera);

	void Collected();

private:
	std::unique_ptr<Collider> collider;

	float width = 75.0f;
	float height = 45.0f;
};