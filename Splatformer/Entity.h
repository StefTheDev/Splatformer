#pragma once

#ifndef ENTITY_H
#define ENTITY_H

#include "Sprite.h"
#include "Collider.h"

enum EntityType {
	PLAYER = 0,
	PLATFORM,
	COIN,
	BALL,
	BUTTON,
	TEXT
};

class Entity
{
public:
	Entity();
	virtual ~Entity();

	//General
	bool Initialise(Vector2 _position, Vector2 dimension);
	virtual void Render(SDL_Renderer * renderer);
	virtual void Listen(SDL_Event event) {}
	virtual void Update();

	//Sprite
	virtual bool LoadSprite(std::shared_ptr<Sprite> _sprite);
	std::shared_ptr<Sprite> GetSprite();

	//Manipulation
	void Transform(Vector2 position);
	void Rotate(float);
	void Scale(float);

	void SetPosition(Vector2 newPosition);
	Vector2 GetPosition();

	Vector2 GetDimensions();

	EntityType GetType();

	bool ShouldDelete();

protected:
	Vector2 position, dimension;
	SDL_Rect source, destination;

	float angle, scale;

	std::shared_ptr<Sprite> sprite;

	EntityType type;

	bool shouldDelete = false;
	bool active = true;

};

#endif

