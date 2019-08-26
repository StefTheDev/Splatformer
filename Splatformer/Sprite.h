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
	Sprite();
	~Sprite();

	//General
	void Render(Camera camera);

	//Textures
	void Load(std::string, SDL_Renderer *, bool animated);

	//Animation
	void Add(std::string, SpriteAnimation);
	void Play(std::string);

	SDL_Texture * GetTexture();

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



