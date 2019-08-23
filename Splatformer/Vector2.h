#pragma once

#ifndef VECTOR_2
#define VECTOR_2

class Vector2
{
public:
	Vector2();
	Vector2(float, float);
	Vector2(const Vector2&);
	~Vector2();

	friend Vector2& operator+(Vector2&, Vector2&);
	friend Vector2& operator-(Vector2&, Vector2&);
	friend Vector2& operator*(Vector2&, Vector2&);
	friend Vector2& operator/(Vector2&, Vector2&);

	Vector2& operator=(Vector2&);

	Vector2& operator+=(Vector2&);
	Vector2& operator-=(Vector2&);
	Vector2& operator*=(Vector2&);
	Vector2& operator/=(Vector2&);

	float x, y;
};

#endif

