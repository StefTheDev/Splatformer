#include "Camera.h"

Camera::Camera() {
	position = Vector2(0.0f, 0.0f) - Vector2(width / 2.0f, height / 2.0f);
}

Camera::Camera(float _width, float _height) {
	width = _width;
	height = _height;

	drawRect = { 0, 0, (int)width, (int)height };
}

void Camera::Initialise(b2World* _gameWorld) {
	DataContainer info = {
		ColliderType::CAM,
		this
	};

	collider = std::make_unique<Collider>(position, info, Vector2(width, height));

	collider->InitialiseKinematic(_gameWorld, true);
	collider->SetCollisionCategory(CATEGORY_CAMERA);
	collider->SetCollisionMask(MASK_CAMERA_DEFAULT);

	SetPosition(collider->body->GetPosition());
}

void Camera::Update() {
	arrived = false;

	if (!targetQueue.empty() && moveSpeed > 0.0f) {
		Vector2 difference((targetQueue.front() - Vector2(width / 2.0f, height / 2.0f)) - position);
		Vector2 direction = difference.Normalised();

		float scale = (difference.Magnitude() / (moveSpeed * deltaTime));

		if (scale > 1.0f) {
			scale = 1.0f;
		} else {
			targetQueue.pop_front();

			arrived = true;

			if (!targetQueue.empty()) {
				Vector2 difference((targetQueue.front() - Vector2(width / 2.0f, height / -2.0f)) - position);

				moveDir = difference.Normalised();
			} else {
				moveDir = Vector2(0.0f, 0.0f);
			}
		}

		position += direction * (moveSpeed * deltaTime * scale);
	}

	// Always update the collider
	collider->body->SetTransform((Vector2(position.x, -position.y) + Vector2(width / 2.0f, height / -2.0f)).AsBox2D(), 0.0f);
}

void Camera::SetPosition(Vector2 _newPosition) {
	position = _newPosition - Vector2(width/2.0f, height/2.0f);
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

	Vector2 difference((targetQueue.front() - Vector2(width / 2.0f, height / -2.0f)) - position);

	moveDir = difference.Normalised();
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

Vector2 Camera::GetMoveVector() {
	return moveDir;
}

SDL_Rect* Camera::GetRect() {
	return &drawRect;
}

bool Camera::Arrived() {
	return arrived;
}
