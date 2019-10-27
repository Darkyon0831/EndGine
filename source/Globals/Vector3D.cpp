#include  "Vector3D.h"

const EG::Vector3D& EG::Vector3D::Zero { 0.0f, 0.0f, 0.0f };

EG::Vector3D::Vector3D(float _x, float _y, float _z)
	: x(_x)
	, y(_y)
	, z(_z)	
{
}

void EG::Vector3D::operator*=(Vector3D& rVector)
{
	x *= rVector.x;
	y *= rVector.y;
	z *= rVector.z;
}

EG::Vector3D EG::Vector3D::operator*(Vector3D& rVector) const
{
	Vector3D newVector;

	newVector.x = x * rVector.x;
	newVector.y = y * rVector.y;
	newVector.z = z * rVector.z;

	return newVector;
}

void EG::Vector3D::operator*=(float rScalar)
{
	x *= rScalar;
	y *= rScalar;
	z *= rScalar;
}

EG::Vector3D EG::Vector3D::operator*(float rScalar) const
{
	Vector3D vector = Vector3D::Zero;

	vector.x = x * rScalar;
	vector.y = y * rScalar;
	vector.z = z * rScalar;

	return vector;
}

void EG::Vector3D::operator/=(float rScalar)
{
	x /= rScalar;
	y /= rScalar;
	z /= rScalar;
}

void EG::Vector3D::operator-=(Vector3D& rVector)
{
	x -= rVector.x;
	y -= rVector.y;
	z -= rVector.z;
}

EG::Vector3D EG::Vector3D::operator-(Vector3D& rVector) const
{
	Vector3D newVector;

	newVector.x = x - rVector.x;
	newVector.y = y - rVector.y;
	newVector.z = z - rVector.z;

	return newVector;
}

void EG::Vector3D::operator+=(Vector3D& rVector)
{
	x += rVector.x;
	y += rVector.y;
	z += rVector.z;
}

EG::Vector3D EG::Vector3D::operator+(Vector3D& rVector) const
{
	Vector3D newVector;

	newVector.x = x + rVector.x;
	newVector.y = y + rVector.y;
	newVector.z = z + rVector.z;

	return newVector;
}

void EG::Vector3D::operator=(float rScalar)
{
	x = rScalar;
	y = rScalar;
	z = rScalar;
}

void EG::Vector3D::Set(float _x, float _y, float _z)
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
