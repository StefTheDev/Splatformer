#pragma once
#include "Utilities.h"

class Camera {
public:
	Camera(float width, float height);

	void SetPosition(Vector2 newPosition);
	Vector2 GetPosition();

	void SetWidth(float newWidth);
	float GetWidth();

	void SetHeight(float newHeight);
	float GetHeight();

	SDL_Rect* GetRect();

private:
	float width, height;
	Vector2 position = {0.0f, 0.0f};

	SDL_Rect drawRect;
};