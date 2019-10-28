#pragma once

#ifndef UTILITIES_H
#define UTILITIES_H

//Native Includes
#include <map>
#include <memory>
#include <iostream>
#include <string>
#include <functional>
#include <vector>
#include <algorithm>

//Dependency Includes
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <SDL_ttf.h>
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
constexpr float PLAYER_WIDTH = 50.0f;
constexpr float PLAYER_HEIGHT = 50.0f;

//Time since last frame in seconds
extern float deltaTime;
extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;
extern int controllersAtStartOfGame;

struct b2BodyDeleter {
	void operator()(b2Body* _body) const {
		_body->GetWorld()->DestroyBody(_body);
	}
};

using b2BodyPtr = std::unique_ptr<b2Body, b2BodyDeleter>;

enum ColliderType {
	PLR = 0,
	PLT,
	CAM,
	RESPAWN,
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

float mapTo(float x, float min, float max, float outMin, float outMax);

template <typename T> 
T sgn(T val) {
	return (T(0) < val) - (val < T(0));
}
#endif