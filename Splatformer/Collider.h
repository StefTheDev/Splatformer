#pragma once
#include "Utilities.h"

constexpr int CATEGORY_PLATFORM			= 0b0000010;
constexpr int CATEGORY_PLAYER			= 0b0000100;

constexpr int CATEGORY_CAMERA			= 0b0001000;
constexpr int CATEGORY_SENSOR			= 0b0010000;
constexpr int CATEGORY_COIN				= 0b0100000;
constexpr int CATEGORY_BALL				= 0b0100000;

constexpr int MASK_PLATFORM_COLLIDE		= 0b0100100;
constexpr int MASK_PLATFORM_NOCOLLIDE	= 0b0000000;

constexpr int MASK_PLAYER_DEFAULT		= 0b1111010;

constexpr int MASK_COIN_DEFAULT			= 0b0000100;

constexpr int MASK_BALL_DEFAULT			= 0b0000110;
constexpr int MASK_BALL_NOCOLLIDE		= 0b0000000;

constexpr int MASK_SENSOR_PLAYER		= 0b0000010;
constexpr int MASK_SENSOR_PLATFORM		= 0b0001000;

constexpr int MASK_CAMERA_DEFAULT		= 0b0000100;

class Collider {
public:
	Collider(Vector2 position, DataContainer colliderData, Vector2 dimensions = { 32.0f, 32.0f });
	~Collider();

	//Initialise immovable collider
	void InitialiseStatic(b2World* worldRef, bool isSensor = false);
	//Initialise collider with dynamic collisions
	void InitialiseDynamic(b2World* worldRef, float density, float friction, float damping, bool IsSensor = false);
	//Initialise collider that is unstoppable but can be moved in code
	void InitialiseKinematic(b2World* worldRef, bool isSensor = false);

	//Initialise immovable collider
	void InitialiseStaticCircle(b2World* worldRef, bool isSensor = false);
	//Initialise collider with circular dynamic collisions
	void InitialiseDynamicCircle(b2World* worldRef, float density, float friction, float damping, bool IsSensor = false);
	//Initialise collider that is unstoppable but can be moved in code
	void InitialiseKinematicCircle(b2World* worldRef, bool isSensor = false);


	//Reminder: If ((categoryA & maskB) != 0 && (categoryB & maskA) != 0) Collisions Can Happen

	//Set the collider category bits
	void SetCollisionCategory(int category);

	//Set the collider mask bits
	void SetCollisionMask(int mask);

	//Returns the position of the body in pixels
	Vector2 GetPosition();

	b2BodyPtr body;

	DataContainer GetDataContainer() { return colliderData; }

private:
	Vector2 position;
	Vector2 dimensions;
	DataContainer colliderData;
};

