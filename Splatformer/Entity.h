#pragma once

#ifndef ENTITY_H
#define ENTITY_H

#include "Sprite.h"
#include "Collider.h"

enum EntityType {
	PLAYER = 0,
	PLATFORM
};

class Entity
{
public:
	Entity();
	~Entity();

	//General
	bool Initialise(Vector2 _position, Vector2 dimension);
	void Render(SDL_Renderer * renderer);
	void Update();

	//Sprite
	bool LoadSprite(std::shared_ptr<Sprite> _sprite);
	std::shared_ptr<Sprite> GetSprite();

	//Manipulation
	void Transform(Vector2 position);
	void Rotate(float);
	void Scale(float);

	void SetPosition(Vector2 newPosition);
	Vector2 GetPosition();

	Vector2 GetDimensions();

	EntityType GetType();

protected:
	Vector2 position, dimension;
	SDL_Rect source, destination;

	float angle, scale;

	std::shared_ptr<Sprite> sprite;

	EntityType type;
};

#endif

