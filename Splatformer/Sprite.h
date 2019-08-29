#pragma once

#ifndef SPRITE_H
#define SPRITE_H

#include "Utilities.h"
#include "Camera.h"

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
	Sprite(std::string fileName, SDL_Renderer * renderer, bool animated);
	~Sprite();

	//Textures
	SDL_Texture * GetTexture();

	//Animation
	void Add(std::string, SpriteAnimation);
	void Play(std::string);

	//Data
	int GetSpeed() const;
	int GetFrames() const;
	int GetIndex() const;
	bool IsAnimated() const;

private:

	std::map<std::string, SpriteAnimation> animations;
	
	int index, frames, speed;
	bool animated = false;

	SDL_Rect srcRect, destRect;
	SDL_Texture* texture;
};

#endif 



