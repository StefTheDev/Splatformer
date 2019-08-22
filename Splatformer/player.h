#pragma once
#include "Utilities.h"

class Player {
public:
	//Player(int controller, b2World& world);

	void Render(SDL_Renderer* renderer);
	void Update();

private:
<<<<<<< Updated upstream

=======
>>>>>>> Stashed changes
	/*
	std::unique_ptr<SDL_GameController> controller;
	
	std::unique_ptr<SDL_Rect> dispBody;

	b2BodyPtr body;
	std::unique_ptr<b2PolygonShape> shape;
	*/
<<<<<<< Updated upstream

	SDL_Texture* texture;
=======
>>>>>>> Stashed changes
};