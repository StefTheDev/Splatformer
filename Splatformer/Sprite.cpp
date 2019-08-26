#include "Sprite.h"

Sprite::Sprite()
{
}


Sprite::~Sprite()
{
}

void Sprite::Render(Camera _camera)
{
	//TODO: Offset non-UI sprites by _camera.position
}

void Sprite::Load(const char * fileName, SDL_Renderer * renderer)
{
	SDL_Surface* surface = IMG_Load(fileName);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	this->texture = texture;
}

void Sprite::Add(const char * name, SpriteAnimation animation)
{
	animations.insert(std::pair<const char *, SpriteAnimation>(name, animation));
}

void Sprite::Play(const char * name)
{
	index = animations[name].index;
	frames = animations[name].frames;
	speed = animations[name].speed;
}
