#pragma once

#ifndef ENTITY_H
#define ENTITY_H

#include "Sprite.h"
#include "Collider.h"

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
	void LoadSprite(std::shared_ptr<Sprite> _sprite);

	//Manipulation
	void Transform(Vector2 position);
	void Rotate(float);
	void Scale(float);

	void SetPosition(Vector2 newPosition);

protected:
	Vector2 position, dimension;
	SDL_Rect source, destination;

	float angle, scale;

	std::shared_ptr<Sprite> sprite;
};

#endif

