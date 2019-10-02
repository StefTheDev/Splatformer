#include "UIText.h"

UIText::UIText() :Entity()
{
	type = BUTTON;
}

UIText::~UIText()
{
	SDL_DestroyTexture(textTexture);
}

bool UIText::Initialise(Vector2 position, std::string text, int size, SDL_Color color, SDL_Renderer* renderer)
{
	TTF_Font* font = TTF_OpenFont("Resources/Fonts/Font.TTF", size);
	SDL_Surface* fontSurface = TTF_RenderText_Solid(font, text.c_str(), color);
	textTexture = SDL_CreateTextureFromSurface(renderer, fontSurface);
	SDL_FreeSurface(fontSurface);

	int width, height;
	SDL_QueryTexture(textTexture, NULL, NULL, &width, &height);

	return Entity::Initialise(Vector2(((WINDOW_WIDTH - width) / 2) + position.x, ((WINDOW_HEIGHT - height) / 2) + position.y), Vector2(width, height));
}

void UIText::Render(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, textTexture, NULL, &destination);
}

bool UIText::LoadSprite(std::shared_ptr<Sprite> _sprite)
{
	return true;
}

SDL_Texture * UIText::GetTexture()
{
	return textTexture;
}
