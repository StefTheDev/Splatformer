#pragma once

#ifndef UTILITIES_H
#define UTILITIES_H

//Native Includes
#include <memory>
#include <string>
#include <vector>

//Dependency Includes
#include <SDL.h>
#include <stdio.h>
#include <Box2D/Box2D.h>

//Pixels per metre for B2D
constexpr float PPM = 32.0f;

struct b2BodyDeleter {
	void operator()(b2Body* _body) const {
		_body->GetWorld()->DestroyBody(_body);
	}
};

//Map a value, x, that exists between lower and upper, to a value between min and max
float MapBetween(float x, float lower, float upper, float min, float max) {
	return ((x - lower) / (upper - lower) * (max - min) + min);
}

#endif // !UTILITIES_H
