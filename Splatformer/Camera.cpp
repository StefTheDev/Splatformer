#include "Camera.h"

Camera::Camera(float _width, float _height) {
	width = _width;
	height = _height;

	drawRect = { 0, 0, width, height };
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

SDL_Rect* Camera::GetRect() {
	return &drawRect;
}
