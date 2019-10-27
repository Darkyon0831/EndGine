#include  "Vector4D.h"

EG::Vector4D::Vector4D(float _x, float _y)
	: x(_x)
	, y(_y)
{
}

void EG::Vector4D::operator*=(Vector4D& rVector)
{
	x *= rVector.x;
	y *= rVector.y;
	z *= rVector.z;
	w *= rVector.w;
}

EG::Vector4D EG::Vector4D::operator*(Vector4D& rVector) const
{
	EG::Vector4D newVector;

	newVector.x = x * rVector.x;
	newVector.y = y * rVector.y;
	newVector.z = z * rVector.z;
	newVector.w = w * rVector.w;

	return newVector;
}

void EG::Vector4D::operator-=(Vector4D& rVector)
{
	x -= rVector.x;
	y -= rVector.y;
	z -= rVector.z;
	w -= rVector.w;
}

EG::Vector4D EG::Vector4D::operator-(Vector4D& rVector) const
{
	Vector4D newVector;

	newVector.x = x - rVector.x;
	newVector.y = y - rVector.y;
	newVector.z = z - rVector.z;
	newVector.w = w - rVector.w;

	return newVector;
}

void EG::Vector4D::operator+=(EG::Vector4D& rVector)
{
	x += rVector.x;
	y += rVector.y;
	z += rVector.z;
	w += rVector.w;
}

EG::Vector4D EG::Vector4D::operator+(Vector4D& rVector) const
{
	Vector4D newVector;

	newVector.x = x + rVector.x;
	newVector.y = y + rVector.y;
	newVector.z = z + rVector.z;
	newVector.w = w + rVector.w;

	return newVector;
}