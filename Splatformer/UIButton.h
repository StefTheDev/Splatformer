#pragma once

#include "Entity.h"

class UIButton : public Entity
{
public:
	UIButton();
	~UIButton();
	bool Initialise(Vector2 position, std::string text, SDL_Renderer* renderer, std::function<void()> onClick);

	void Render(SDL_Renderer* renderer) override;
	void Listen(SDL_Event event) override;

private:
	SDL_Texture* textTexture;
	std::function<void()> onClick;
	bool IsHover(int x, int y);

	void click();
};

