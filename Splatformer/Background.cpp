#include "Background.h"



Background::Background(Vector2 _position)
{

	type = BACKGROUND;
	_position.y *= -1.0f;

	_position.x *= width;
	_position.y *= height;

	Entity::Initialise(_position, { width, height });
}


Background::~Background()
{
}


void Background::Initialise(b2World* world, std::shared_ptr<Sprite> _coinSprite) {

	if (!LoadSprite(_coinSprite)) return;

	GetSprite()->Add("idle", SpriteAnimation{ 0, 1, 500 }); //Index, frames, speed
}

void Background::Update(Camera* gameCamera) {

	GetSprite()->Play("idle");

	Entity::Update();
}

void Background::Render(SDL_Renderer * renderer) {

	sprite->Draw(renderer, Vector2(0.0f, 0.0f), Vector2(1920, 1080), 0.0, 0, 0);

}