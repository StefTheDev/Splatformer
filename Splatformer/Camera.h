#pragma once
#include "Utilities.h"

class Camera {
public:
	Camera() = default;
	Camera(float width, float height);

	void Update();

	void SetPosition(Vector2 newPosition);
	Vector2 GetPosition();

	void SetWidth(float newWidth);
	float GetWidth();

	void SetHeight(float newHeight);
	float GetHeight();

	void SetTargetPosition(Vector2 newTarget);
	Vector2 GetTargetPosition();

	void SetMoveSpeed(float newMoveSpeed);
	float GetMoveSpeed();

	SDL_Rect* GetRect();

private:
	float width, height;
	Vector2 position = {0.0f, 0.0f};

	Vector2 targetPosition = { 0.0f, 0.0f };
	//The number of pixels to move per second toward the target position
	float moveSpeed = 0.0f;

	SDL_Rect drawRect;
};