#pragma once
#include <SDL.h>

struct Vector2D
{
public:
	Vector2D(int x, int y) : x(x), y(y) {}

	Vector2D& operator+=(const Vector2D& rhs)
	{
		this->x += rhs.x;
		this->y += rhs.y;

		return *this;
	}

	Vector2D& operator-=(const Vector2D& rhs)
	{
		this->x -= rhs.x;
		this->y -= rhs.y;

		return *this;
	}

	void SetPositionTo(SDL_Rect& rect)
	{
		rect.x = this->x;
		rect.y = this->y;
	}

private:
	int x;
	int y;
};