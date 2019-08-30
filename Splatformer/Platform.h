#pragma once
#include "Utilities.h"
#include "Entity.h"

class Platform : public Entity {
public:
	Platform(Vector2 position);

	void Initialise(b2World* world, std::shared_ptr<Sprite> platformSprite);
	void Update(Camera* _gameCamera);

	void SetCanCollide(bool canCollide);
	bool CanCollide();

private:
	std::unique_ptr<Collider> collider;

	bool canCollide = true;

	float width = 75.0f;
	float height = 40.0f;
};