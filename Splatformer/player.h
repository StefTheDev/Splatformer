#pragma once
#include "Utilities.h"

class Player {
public:
	Player(int controller, b2World& world);

	void Render();
	void Update();

private:
	std::unique_ptr<SDL_GameController> controller;
	
	std::unique_ptr<SDL_Rect> dispBody;

	std::unique_ptr<b2Body> body;
	std::unique_ptr<b2PolygonShape> shape;
};