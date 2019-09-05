#pragma once

#include "Utilities.h"

class TextLabel
{
public:
	TextLabel(std::string message, TTF_Font * font, SDL_Color color, SDL_Rect rect);
	~TextLabel();

	void Render(SDL_Renderer * renderer);

	void SetColor(SDL_Color color);
	void SetPosition(Vector2 position);
	void SetDimension(Vector2 dimension);

private:
	std::string message;

	SDL_Surface * surface;
	SDL_Texture * texture;
	TTF_Font * font = nullptr;

	Vector2 position, dimension;
	SDL_Color color;
};

