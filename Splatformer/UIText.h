#pragma once

#include "Entity.h"

class UIText : public Entity
{
public:
	UIText();
	~UIText();

	bool Initialise(Vector2 position, std::string text, int size, SDL_Color color, SDL_Renderer * renderer);

	void Render(SDL_Renderer* renderer) override;

	bool LoadSprite(std::shared_ptr<Sprite> _sprite) override;

	SDL_Texture* GetTexture();

private:
	SDL_Texture* textTexture;
};
