#include "Jumper.h"

Jumper::Jumper()
{

}

Jumper::~Jumper()
{

}

bool Jumper::Initialise(SDL_Renderer * renderer)
{
	if(!LoadSprite(std::make_shared<Sprite>("Resources/Textures/Player.png", renderer, true))) return false;

	GetSprite()->Add("idle", SpriteAnimation{ 0, 4, 500 }); //Index, frames, speed
	GetSprite()->Add("walk", SpriteAnimation{ 1, 6, 50 });

	return Entity::Initialise(Vector2{ 64, 64 }, Vector2{ 32, 32 });
}

void Jumper::Update()
{
	if (GetSprite()->GetTexture() != nullptr) {
		std::cout << "Texture works" << std::endl;
	}
	GetSprite()->Play("idle");
	return Entity::Update();
}



