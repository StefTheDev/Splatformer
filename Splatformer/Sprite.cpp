#include "Sprite.h"

Sprite::Sprite(std::string fileName, SDL_Renderer * renderer, bool animated)
{
	SDL_Surface* surface = IMG_Load(fileName.c_str());
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	this->animated = animated;
	this->texture = texture;
}

Sprite::~Sprite()
{

}

void Sprite::Add(std::string name, SpriteAnimation animation)
{
	animations.insert(std::pair<std::string, SpriteAnimation>(name, animation));
}

void Sprite::Play(std::string name)
{
	index = animations[name].index;
	frames = animations[name].frames;
	speed = animations[name].speed;
}

SDL_Texture * Sprite::GetTexture()
{
	return texture;
}

int Sprite::GetSpeed() const
{
	return speed;
}

int Sprite::GetFrames() const
{
	return frames;
}

int Sprite::GetIndex() const
{
	return index;
}

bool Sprite::IsAnimated() const
{
	return animated;
}
