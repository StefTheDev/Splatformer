#pragma once

#include "Utilities.h"

#ifndef VECTOR_2
#define VECTOR_2

class Vector2
{
public:
	Vector2();
	Vector2(float, float);
	Vector2(const Vector2&);
	Vector2(b2Vec2);
	~Vector2();

	friend Vector2& operator+(Vector2, Vector2);
	friend Vector2& operator-(Vector2, Vector2);
	friend Vector2& operator*(Vector2, float);
	friend Vector2& operator/(Vector2&, float);



	Vector2& operator=(Vector2);

	Vector2& operator+=(Vector2&);
	Vector2& operator-=(Vector2&);
	Vector2& operator*=(float);
	Vector2& operator/=(float);

	float Magnitude();
	Vector2 Normalised();
	float Dot(Vector2 other);

	b2Vec2 AsBox2D();

	float x, y;
};

std::ostream& operator<<(std::ostream& _stream, Vector2 _vec);

#endif

