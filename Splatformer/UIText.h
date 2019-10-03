#pragma once

#include "Entity.h"

class UIText : public Entity
{
public:
	UIText();
	~UIText();

	bool Initialise(Vector2 position, std::string text, int size, SDL_Color color, SDL_Renderer * renderer);

	void Render(SDL_Renderer* renderer) override;
	void Update() override;

	void SetText(std::string _text);

	bool LoadSprite(std::shared_ptr<Sprite> _sprite) override;

	SDL_Texture* GetTexture();

private:
	int size;
	std::string text;
	SDL_Color color;

	SDL_Renderer * renderer;
	SDL_Texture* textTexture;
	TTF_Font* font;
};
