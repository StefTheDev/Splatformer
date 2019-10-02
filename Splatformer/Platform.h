#pragma once
#include "Utilities.h"
#include "Entity.h"

struct TileInfo {
	Vector2 position;
	Vector2 dimensions;
};

class Platform : public Entity {
public:
	Platform(TileInfo info);

	virtual void Initialise(b2World* world, std::shared_ptr<Sprite> platformSprite);
	virtual void Update(Camera* gameCamera, float _sceneTime);

	void SetCanCollide(bool canCollide);
	bool CanCollide();

	Collider* GetCollider() { return collider.get(); }

protected:
	TileInfo thisInfo;

	std::unique_ptr<Collider> collider;

	bool canCollide = true;

	float width = 75.0f;
	float height = 40.0f;
};