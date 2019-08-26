#pragma once
#include "Utilities.h"

constexpr int CATEGORY_PLATFORM			= 0b000010;
constexpr int CATEGORY_PLAYER			= 0b000100;
constexpr int CATEGORY_SENSOR			= 0b001000;

constexpr int MASK_PLATFORM_COLLIDE		= 0b000100;
constexpr int MASK_PLATFORM_NOCOLLIDE	= 0b001000;

constexpr int MASK_PLAYER_DEFAULT		= 0b000010;

constexpr int MASK_SENSOR_PLAYER		= 0b000010;
constexpr int MASK_SENSOR_PLATFORM		= 0b001000;

class Collider {
public:
	Collider(Vector2 position, Vector2 dimensions = { 32.0f, 32.0f });

	void InitialiseStatic(b2World* worldRef, bool isSensor = false);
	void InitialiseDynamic(b2World* worldRef, float density, float friction, float damping, bool IsSensor = false);
	void InitialiseKinematic(b2World* worldRef, bool isSensor = false);

	//Reminder: If ((categoryA & maskB) != 0 && (categoryB & maskA) != 0) Collisions Can Happen

	//Set the collider category bits
	void SetCollisionCategory(int category);

	//Set the collider mask bits
	void SetCollisionMask(int mask);

	b2BodyPtr body;

private:
	Vector2 position;
	Vector2 dimensions;
};