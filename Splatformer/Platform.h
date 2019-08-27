#pragma once
#include "Utilities.h"
#include "Entity.h"

class Platform : public Entity {
public:
	Platform();

	void Initialise(Vector2 position, b2World* world, std::shared_ptr<Sprite> platformSprite);
	void Update(Camera* _gameCamera);

	void SetCanCollide(bool canCollide);
	bool CanCollide();

private:
	std::unique_ptr<Collider> collider;

	bool canCollide = true;

	float width = 100.0f;
	float height = 100.0f;
};