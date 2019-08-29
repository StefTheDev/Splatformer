#pragma once

#include "Entity.h"

class Jumper : public Entity
{
public:
	Jumper();
	~Jumper();

	bool Initialise(SDL_Renderer * renderer);
	void Update();
};

