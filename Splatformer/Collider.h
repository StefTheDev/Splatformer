#pragma once
#include "Utilities.h"

#define PLATFORM_MASK_DEFAULT 0b0001
#define PLATFORM_CATEGORY_COLLIDE 0b0001
#define PLATFORM_CATEGORY_NO_COLLIDE 0b0010

class Collider {
public:
	Collider(Vector2 position, Vector2 dimensions = { 32.0f, 32.0f });

	void InitialiseStatic(b2World* worldRef);
	void InitialiseDynamic(b2World* worldRef, float density, float friction, float damping);

	//Reminder: if ((categoryA & maskB) != 0 && (categoryB & maskA) != 0) Collisions Can Happen

	//Set the collider category bits
	void SetCollisionCategory(int category);

	//Set the collider mask bits
	void SetCollisionMask(int mask);

	b2BodyPtr body;

private:
	Vector2 position;
	Vector2 dimensions;
};