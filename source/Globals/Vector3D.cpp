#include  "Vector3D.h"

const EG::Vector3D& EG::Vector3D::Zero { 0.0f, 0.0f, 0.0f };

EG::Vector3D::Vector3D(float _x, float _y, float _z)
	: x(_x)
	, y(_y)
	, z(_z)	
{
}

void EG::Vector3D::operator*=(const Vector3D& rVector)
{
	x *= rVector.x;
	y *= rVector.y;
	z *= rVector.z;
}

EG::Vector3D EG::Vector3D::operator*(const Vector3D& rVector) const
{
	Vector3D newVector;

	newVector.x = x * rVector.x;
	newVector.y = y * rVector.y;
	newVector.z = z * rVector.z;

	return newVector;
}

void EG::Vector3D::operator*=(const float& rScalar)
{
	x *= rScalar;
	y *= rScalar;
	z *= rScalar;
}

EG::Vector3D EG::Vector3D::operator*(const float& rScalar) const
{
	Vector3D vector = Vector3D::Zero;

	vector.x = x * rScalar;
	vector.y = y * rScalar;
	vector.z = z * rScalar;

	return vector;
}

void EG::Vector3D::operator/=(const float& rScalar)
{
	x /= rScalar;
	y /= rScalar;
	z /= rScalar;
}

void EG::Vector3D::operator-=(const Vector3D& rVector)
{
	x -= rVector.x;
	y -= rVector.y;
	z -= rVector.z;
}

EG::Vector3D EG::Vector3D::operator-(const Vector3D& rVector) const
{
	Vector3D newVector;

	newVector.x = x - rVector.x;
	newVector.y = y - rVector.y;
	newVector.z = z - rVector.z;

	return newVector;
}

void EG::Vector3D::operator+=(const Vector3D& rVector)
{
	x += rVector.x;
	y += rVector.y;
	z += rVector.z;
}

EG::Vector3D EG::Vector3D::operator+(const Vector3D& rVector) const
{
	Vector3D newVector;

	newVector.x = x + rVector.x;
	newVector.y = y + rVector.y;
	newVector.z = z + rVector.z;

	return newVector;
}

void EG::Vector3D::operator=(const float& rScalar)
{
	x = rScalar;
	y = rScalar;
	z = rScalar;
}

void EG::Vector3D::Set(const float _x, const float _y, const float _z)
{
	x = _x;
	y = _y;
	z = _z;
}

void EG::Vector3D::Normilize()
{
	*this /= this->Length();

	int debug = 0;
}

float EG::Vector3D::Length() const
{
	return sqrt(x * x + y * y + z * z);
}

EG::Vector3D EG::Vector3D::CrossProduct(const Vector3D& rOther) const
{
	Vector3D newVector;
	newVector.x = y * rOther.z - z * rOther.y;
	newVector.y = z * rOther.x - x * rOther.z;
	newVector.z = x * rOther.y - y * rOther.x;

	return newVector;
}

float EG::Vector3D::DotProduct(const Vector3D& rOther) const
{
	return x * rOther.x + y * rOther.y + z * rOther.z;
}

EG::Vector3D EG::Vector3D::CrossProduct(const Vector3D& v1, const Vector3D& v2)
{
	Vector3D newVector;
	newVector.x = v1.y * v2.z - v1.z * v2.y;
	newVector.y = v1.z * v2.x - v1.x * v2.z;
	newVector.z = v1.x * v2.y - v1.y * v2.x;

	return newVector;
}

float EG::Vector3D::DotProduct(const Vector3D& v1, const Vector3D& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}
