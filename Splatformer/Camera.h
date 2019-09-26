#pragma once
#include "Utilities.h"
#include <deque>
#include "Collider.h"

class Camera {
public:
	Camera();
	Camera(float width, float height);

	void Initialise(b2World* gameWorld);
	void Update();

	void SetPosition(Vector2 newPosition);
	Vector2 GetPosition();

	void SetWidth(float newWidth);
	float GetWidth();

	void SetHeight(float newHeight);
	float GetHeight();

	void PushTargetBack(Vector2 newTarget);
	void PushTargetFront(Vector2 newTarget);
	void SetTargetPosition(Vector2 newTarget);
	Vector2 GetTargetPosition();

	//Set the number of pixels to move per second toward the target position
	void SetMoveSpeed(float newMoveSpeed);
	float GetMoveSpeed();

	SDL_Rect* GetRect();


	std::unique_ptr<Collider> collider;
private:
	float width, height;
	Vector2 position;

	std::deque<Vector2> targetQueue;

	//The number of pixels to move per second toward the target position
	float moveSpeed = 0.0f;

	SDL_Rect drawRect;
};