#include "Entity.h"

Entity::Entity()
{

}

Entity::~Entity()
{
}

bool Entity::Initialise(Vector2 _position, Vector2 dimension)
{
	position = _position;
	angle = 0.0f;
	scale = 1.0f;

	source.x = source.y = 0;
	source.w = dimension.x;
	source.h = dimension.y;

	return true;
}

void Entity::Render(SDL_Renderer * renderer)
{

	SDL_RenderCopyEx(
		renderer,
		sprite->GetTexture(),
		&source,
		&destination,
		angle,
		NULL,
		SDL_FLIP_NONE
	);
}

void Entity::Update()
{
	if (sprite->IsAnimated()) source.x = source.w * static_cast<int>((SDL_GetTicks() / sprite->GetSpeed()) % sprite->GetFrames());
	source.y = sprite->GetIndex() * dimension.y;

	destination.x = static_cast<int>(position.x);
	destination.y = static_cast<int>(position.y);
	destination.w = dimension.x * static_cast<int>(scale);
	destination.h = source.h * static_cast<int>(scale);
}

void Entity::LoadSprite(std::shared_ptr<Sprite> _sprite)
{
	sprite = _sprite;
}

void Entity::Transform(Vector2 position)
{
	this->position += position;
}

void Entity::Rotate(float angle)
{
	this->angle += angle;
}

void Entity::Scale(float scale)
{
	this->scale += scale;
}

void Entity::SetPosition(Vector2 _newPosition) {
	position = _newPosition;
}
