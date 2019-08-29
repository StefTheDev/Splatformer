#include "Vector2.h"

#include <math.h>

Vector2::Vector2()
{
	this->x = 0.0f;
	this->y = 0.0f;
}

Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2::Vector2(const Vector2 & v)
{
	x = v.x;
	y = v.y;
}

Vector2::Vector2(b2Vec2 bv) 
{
	float newX = bv.x * PPM;
	float newY = bv.y * -PPM;

	x = newX;
	y = newY;
}

Vector2::~Vector2()
{
}

Vector2& Vector2::operator=(Vector2 v) 
{
	x = v.x;
	y = v.y;

	return *this;
}

Vector2 & Vector2::operator+=(Vector2 & v)
{
	x += v.x;
	y += v.y;

	return *this;
}

Vector2 & Vector2::operator-=(Vector2 & v)
{
	x -= v.x;
	y -= v.y;

	return *this;
}

Vector2 & Vector2::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;

	return *this;
}

Vector2 & Vector2::operator/=(float scalar)
{
	x /= scalar;
	y /= scalar;

	return *this;
}

float Vector2::Magnitude() {
 	return sqrtf(powf(x, 2.0f) + powf(y, 2.0f));
}

Vector2 Vector2::Normalised() {
	Vector2 outVec(x, y);

	outVec.x /= Magnitude();
	outVec.y /= Magnitude();

	return outVec;
}

b2Vec2 Vector2::AsBox2D() {
	return b2Vec2(x/PPM, y/PPM);
}

Vector2 & operator+(Vector2 v1, Vector2 v2)
{
	Vector2 outVec(v1);
	outVec.x += v2.x;
	outVec.y += v2.y;

	return outVec;
}

Vector2 & operator-(Vector2 v1, Vector2 v2)
{
	Vector2 outVec(v1);

	outVec.x -= v2.x;
	outVec.y -= v2.y;

	return outVec;
}

Vector2 & operator*(Vector2 & v1, float scalar)
{
	Vector2 outVec(v1);
	outVec.x *= scalar;
	outVec.y *= scalar;

	return outVec;
}

Vector2 & operator/(Vector2 & v1, float scalar)
{
	Vector2 outVec(v1);
	outVec.x /= scalar;
	outVec.y /= scalar;

	return outVec;
}
