#pragma once

#include "Entity.h"

class UIButton : public Entity
{
public:
	UIButton();
	~UIButton();
	bool Initialise(Vector2 position, std::string text, int size, SDL_Renderer * renderer, std::function<void()> onClick);

	void Update() override;
	void Render(SDL_Renderer* renderer) override;
	void Listen(SDL_Event event) override;

	void SetHover(bool value);

	void SetUp(UIButton* uiElement);
	void SetDown(UIButton* uiElement);
	void SetLeft(UIButton* uiElement);
	void SetRight(UIButton* uiElement);

	bool LoadSprite(std::shared_ptr<Sprite> _sprite) override;

	SDL_Texture* GetTexture();

private:
	SDL_Texture* textTexture;
	void SetFocus(int which);
	UIButton *up = nullptr, *down = nullptr, *left = nullptr, *right = nullptr;

	std::function<void()> onClick;
	bool IsHover(int x, int y);

	void click();
	bool hovering = false;
	bool justHovered = false;
};

