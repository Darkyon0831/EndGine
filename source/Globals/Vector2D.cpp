#include  "Vector2D.h"

EG::Vector2D::Vector2D(float _x, float _y)
	: x(_x)
	, y(_y)
{
}

void EG::Vector2D::operator*=(Vector2D& rVector)
{
	x *= rVector.x;
	y *= rVector.y;
}

EG::Vector2D EG::Vector2D::operator*(Vector2D& rVector) const
{
	Vector2D newVector;

	newVector.x = x * rVector.x;
	newVector.y = y * rVector.y;

	return newVector;
}

void EG::Vector2D::operator-=(Vector2D& rVector)
{
	x -= rVector.x;
	y -= rVector.y;
}

EG::Vector2D EG::Vector2D::operator-(Vector2D& rVector) const
{
	Vector2D newVector;

	newVector.x = x - rVector.x;
	newVector.y = y - rVector.y;

	return newVector;
}

void EG::Vector2D::operator+=(Vector2D& rVector)
{
	x += rVector.x;
	y += rVector.y;
}

EG::Vector2D EG::Vector2D::operator+(Vector2D& rVector) const
{
	Vector2D newVector;

	newVector.x = x + rVector.x;
	newVector.y = y + rVector.y;

	return newVector;
}