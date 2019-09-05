#pragma once
#include "Utilities.h"
#include "Entity.h"

class Platform : public Entity {
public:
	Platform(Vector2 position);

	virtual void Initialise(b2World* world, std::shared_ptr<Sprite> platformSprite);
	virtual void Update(Camera* gameCamera, float _sceneTime);

	void SetCanCollide(bool canCollide);
	bool CanCollide();

protected:
	std::unique_ptr<Collider> collider;

	bool canCollide = true;

	float width = 75.0f;
	float height = 40.0f;
};