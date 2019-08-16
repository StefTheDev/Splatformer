#pragma once

#ifndef SPRITE_H
#define SPRITE_H

#include "Utilities.h"

struct SpriteAnimation
{
	int index, frames, speed;

	SpriteAnimation(int index = 0, int frames = 0, int speed = 100)
	{
		this->index = index;
		this->frames = frames;
		this->speed = speed;
	}
};

class Sprite
{
public:
	Sprite();
	~Sprite();

	//General
	void Render();
	void Update();

	//Textures
	void Load(const char *, SDL_Renderer * renderer);


	//Animation
	void Add(const char *, SpriteAnimation);
	void Play(const char *);

private:

	//Animation
	std::map<const char*, SpriteAnimation> animations;
	int index, frames, speed;

	SDL_Texture* texture;
};

#endif 



