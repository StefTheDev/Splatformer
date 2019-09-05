#include "Camera.h"

Camera::Camera() {
	position = Vector2(0.0f, 0.0f);
}

Camera::Camera(float _width, float _height) {
	width = _width;
	height = _height;

	drawRect = { 0, 0, (int)width, (int)height };
}

void Camera::Update() {
	if (!targetQueue.empty()) {
		Vector2 difference(targetQueue.front() - position);
		Vector2 direction = difference.Normalised();

		float scale = (difference.Magnitude() / (moveSpeed * deltaTime));

		if (scale > 1.0f) {
			scale = 1.0f;
		} else {
			targetQueue.pop_front();
		}

		position += direction * (moveSpeed * deltaTime * scale);
	}
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

void Camera::PushTargetBack(Vector2 _newTarget) {
	targetQueue.push_back(_newTarget);
}

void Camera::PushTargetFront(Vector2 _newTarget) {
	targetQueue.push_front(_newTarget);
}

void Camera::SetTargetPosition(Vector2 _newTarget) {
	if (targetQueue.empty()) {
		PushTargetBack(_newTarget);
	} else {
		targetQueue.front() = _newTarget;
	}
}

Vector2 Camera::GetTargetPosition() {
	return targetQueue.front();
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
