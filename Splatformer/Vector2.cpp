#include "Vector2.h"

Vector2::Vector2()
{
	this->x = 1;
	this->y = 1;
}

Vector2::Vector2(float, float)
{
}

Vector2::Vector2(Vector2 &)
{
}

Vector2::~Vector2()
{
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

Vector2 & Vector2::operator*=(Vector2 & v)
{
	x *= v.x;
	y *= v.y;

	return *this;
}

Vector2 & Vector2::operator/=(Vector2 & v)
{
	x /= v.x;
	y /= v.y;

	return *this;
}

Vector2 & operator+(Vector2 & v1, Vector2 &v2)
{
	v1.x += v2.x;
	v1.y += v2.y;

	return v1;
}

Vector2 & operator-(Vector2 & v1, Vector2 &v2)
{
	v1.x -= v2.x;
	v1.y -= v2.y;

	return v1;
}

Vector2 & operator*(Vector2 & v1, Vector2 &v2)
{
	v1.x *= v2.x;
	v1.y *= v2.y;

	return v1;
}

Vector2 & operator/(Vector2 & v1, Vector2 &v2)
{
	v1.x /= v2.x;
	v1.y /= v2.y;

	return v1;
}
