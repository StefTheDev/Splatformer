#pragma once

//#ifndef _DEBUG
//#define _ITERATOR_DEBUG_LEVEL 1
//#endif // _DEBUG

#ifndef UTILITIES_H
#define UTILITIES_H

//Native Includes
#include <map>
#include <memory>
#include <iostream>
#include <string>
#include <vector>

//Dependency Includes
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <Box2D/Box2D.h>

//Local Includes
#include "Vector2.h"
#include "input.h"

//Constant expressions

//Into Box2D: Divide values by PPM
//Out of Box2D: Multiply by PPM

//Pixels per metre for B2D
constexpr float PPM = 32.0f;

//Global Variables

//Time since last frame in seconds
extern float deltaTime;

struct b2BodyDeleter {
	void operator()(b2Body* _body) const {
		_body->GetWorld()->DestroyBody(_body);
	}
};

using b2BodyPtr = std::unique_ptr<b2Body, b2BodyDeleter>;

enum ColliderType {
	PLR = 0,
	PLT,
	ECOIN,
	CBALL,
	OTHER
};

struct DataContainer {
	ColliderType type;
	void* data;
};

class PlatformingListener : public b2ContactListener {
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
};
#endif