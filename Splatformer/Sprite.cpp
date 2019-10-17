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
	if (texture != nullptr) SDL_DestroyTexture(texture);
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

void Sprite::Draw(SDL_Renderer* _renderer, Vector2 _position, Vector2 _dimensions, double _angle, int _frame, int _layer) {
	if (texture == nullptr) return;

	SDL_Rect dest = {
		_position.x,
		_position.y,
		_dimensions.x,
		_dimensions.y
	};

	SDL_RenderCopyEx(
		_renderer,
		texture,
		&srcRect,
		&dest,
		_angle,
		NULL,
		SDL_FLIP_NONE
	);
}

void Sprite::SetSource(Vector2 _dimensions) {
	srcRect.x = srcRect.y = 0;
	srcRect.w = _dimensions.x;
	srcRect.h = _dimensions.y;
}