#include "Camera.h"

Camera::Camera(float _width, float _height) {
	width = _width;
	height = _height;

	drawRect = { 0, 0, (int)width, (int)height };
}

void Camera::Update() {
	Vector2 direction = (targetPosition - position).Normalised();

	position += direction * (moveSpeed * deltaTime);
}

void Camera::SetPosition(Vector2 _newPosition) {
	position = _newPosition;
}

Vector2 Camera::GetPosition() {
	return position;
}

void Camera::SetWidth(float _newWidth) {
	width = _newWidth;
}

float Camera::GetWidth() {
	return width;
}

void Camera::SetHeight(float _newHeight) {
	height = _newHeight;
}

float Camera::GetHeight() {
	return height;
}

void Camera::SetTargetPosition(Vector2 _newTarget) {
	targetPosition = _newTarget;
}

Vector2 Camera::GetTargetPosition() {
	return targetPosition;
}

void Camera::SetMoveSpeed(float _newMoveSpeed) {
	moveSpeed = _newMoveSpeed;
}

float Camera::GetMoveSpeed() {
	return moveSpeed;
}

SDL_Rect* Camera::GetRect() {
	return &drawRect;
}
