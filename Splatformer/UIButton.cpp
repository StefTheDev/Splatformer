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

void UIButton::Update() {
	Entity::Update();
	justHovered = false;

	if (hovering) {
		SDL_SetTextureColorMod(textTexture, 255, 0, 255);
	} else {
		SDL_SetTextureColorMod(textTexture, 250, 250, 250);
	}
}

void UIButton::Render(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, textTexture, NULL, &destination);
}

void UIButton::Listen(SDL_Event event) {
	if ((!hovering) || justHovered) return;

	switch (event.type)
	{
		case SDL_CONTROLLERBUTTONDOWN:
		{
			switch(event.cbutton.button){
			case (SDL_CONTROLLER_BUTTON_A): {
				click();
				break;
			}
			case (SDL_CONTROLLER_BUTTON_DPAD_UP):{
				SetFocus(0);
				break;
			}
			case (SDL_CONTROLLER_BUTTON_DPAD_RIGHT):{
				SetFocus(1);
				break;
			}
			case (SDL_CONTROLLER_BUTTON_DPAD_DOWN):{
				SetFocus(2);
				break;
			}
			case (SDL_CONTROLLER_BUTTON_DPAD_LEFT):
			{
				SetFocus(3);
				break;
			}default: {
				break;
			}
			}
		break;
		}
	}

	Entity::Listen(event);
}

void UIButton::SetFocus(int _which) {
	switch (_which) {
	case(0): {
		if (up == nullptr) return;
		up->SetHover(true);
		break;
	}
	case(1): {
		if (right == nullptr) return;
		right->SetHover(true);
		break;
	}
	case(2):{
		if (down == nullptr) return;
		down->SetHover(true);
		break;
	}
	case(3):{
		if (left == nullptr) return;
		left->SetHover(true);
		break;
	}
	default: {
		return;
	}
	}
	SoundManager::PlaySound("Menu");
	SetHover(false);
}

void UIButton::SetHover(bool _value) {
	hovering = _value;
	justHovered = _value;
}

void UIButton::SetUp(UIButton* _uiElement) {
	up = _uiElement;
}

void UIButton::SetDown(UIButton* _uiElement) {
	down = _uiElement;
}

void UIButton::SetLeft(UIButton* _uiElement) {
	left = _uiElement;
}

void UIButton::SetRight(UIButton* _uiElement) {
	right = _uiElement;
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
