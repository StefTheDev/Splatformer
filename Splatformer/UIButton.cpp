#include "UIButton.h"
#include "soundmanager.h"

UIButton::UIButton() :Entity()
{
	type = BUTTON;
}

UIButton::~UIButton()
{
	SDL_DestroyTexture(textTexture);
}

bool UIButton::Initialise(Vector2 position, std::string text, int size, SDL_Renderer* renderer, std::function<void()> onClick)
{
	this->onClick = onClick;
	TTF_Font* font = TTF_OpenFont("Resources/Fonts/Font.TTF", size);
	SDL_Surface* fontSurface = TTF_RenderText_Solid(font, text.c_str(), SDL_Color{ 255, 255, 255 });
	textTexture = SDL_CreateTextureFromSurface(renderer, fontSurface);
	SDL_FreeSurface(fontSurface);
	TTF_CloseFont(font);

	int width, height;
	SDL_QueryTexture(textTexture, NULL, NULL, &width, &height);

	return Entity::Initialise(Vector2(((WINDOW_WIDTH - width) / 2) + position.x, ((WINDOW_HEIGHT - height) / 2) + position.y), Vector2(width, height));
}

void UIButton::Render(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, textTexture, NULL, &destination);
}

void UIButton::Listen(SDL_Event event)
{
	switch (event.type)
	{
		case SDL_MOUSEMOTION: {
			if (IsHover(event.motion.x, event.motion.y)) {
				SDL_SetTextureColorMod(textTexture, 255, 0, 255);
				if (hovering == false)
				{
					SoundManager::PlaySound("Menu");
					hovering = true;
				}
			}
			else {
				SDL_SetTextureColorMod(textTexture, 250, 250, 250);
				if(hovering == true) hovering = false;
			}
			break;
		}
		case SDL_MOUSEBUTTONDOWN: {

			if (IsHover(event.motion.x, event.motion.y)) click();
			break;
		}
	}
	Entity::Listen(event);
}

bool UIButton::LoadSprite(std::shared_ptr<Sprite> _sprite)
{
	return true;
}

SDL_Texture * UIButton::GetTexture()
{
	return textTexture;
}

bool UIButton::IsHover(int x, int y)
{
	return ((x > destination.x) && (x < destination.x + destination.w) && (y > destination.y) && (y < destination.y + destination.h));
}

void UIButton::click()
{
	return onClick();
}
