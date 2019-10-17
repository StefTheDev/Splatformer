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
	void Draw(SDL_Renderer* renderer, Vector2 position, Vector2 dimensions, double angle = 0.0, int frame = 0, int layer = 0);

	//Data
	int GetSpeed() const;
	int GetFrames() const;
	int GetIndex() const;
	bool IsAnimated() const;

	void SetSource(Vector2 dimensions);

private:

	std::map<std::string, SpriteAnimation> animations;
	
	int index, frames, speed;
	bool animated = false;

	SDL_Rect srcRect, destRect;
	SDL_Texture* texture;
};

#endif 



