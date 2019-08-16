#pragma once

#ifndef ENTITY_H
#define ENTITY_H

#include "Sprite.h"

class Entity
{
public:
	Entity();
	~Entity();

	//Sprite
	void LoadTexture(const char *);

	//Collision
	//Box2D

	//Transform
	void Translate(Vector2 &);
	void Scale(Vector2 &);
	void Rotate(float);

private:
	Vector2 position, scale;
	float rotation;
};

#endif

