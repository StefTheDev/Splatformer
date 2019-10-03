#include "UIText.h"

UIText::UIText() :Entity()
{
	type = BUTTON;
}

UIText::~UIText()
{
	if(textTexture != nullptr) SDL_DestroyTexture(textTexture);
	if(font != nullptr) TTF_CloseFont(font);
}

bool UIText::Initialise(Vector2 position, std::string text, int size, SDL_Color color, SDL_Renderer* renderer)
{
	this->text = text;
	this->size = size;
	this->color = color;
	this->renderer = renderer;

	font = TTF_OpenFont("Resources/Fonts/Font.TTF", size);
	SDL_Surface* fontSurface = TTF_RenderText_Solid(font, text.c_str(), color);
	textTexture = SDL_CreateTextureFromSurface(renderer, fontSurface);
	SDL_FreeSurface(fontSurface);

	int width, height;
	SDL_QueryTexture(textTexture, NULL, NULL, &width, &height);

	return Entity::Initialise(Vector2(position.x, position.y), Vector2(width, height));
}

void UIText::Render(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, textTexture, NULL, &destination);
}

void UIText::Update()
{
	if (textTexture != nullptr) SDL_DestroyTexture(textTexture);

	SDL_Surface* fontSurface = TTF_RenderText_Solid(font, text.c_str(), color);
	textTexture = SDL_CreateTextureFromSurface(renderer, fontSurface);
	SDL_FreeSurface(fontSurface);

	int width, height;

	SDL_QueryTexture(textTexture, NULL, NULL, &width, &height);
	
	destination.x = ((WINDOW_WIDTH - width) / 2) + position.x;
	destination.y = ((WINDOW_HEIGHT - height) / 2) + position.y;
	destination.w = width;
	destination.h = height;
}

void UIText::SetText(std::string _text) {
	text = _text;
}

bool UIText::LoadSprite(std::shared_ptr<Sprite> _sprite)
{
	return true;
}

SDL_Texture * UIText::GetTexture()
{
	return textTexture;
}
