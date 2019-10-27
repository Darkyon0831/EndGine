#pragma once

#include <cmath>

namespace EG
{	
	class Vector3D
	{
	public:

		Vector3D() = default;
		Vector3D(float x, float y, float z);

		void operator*= (Vector3D& rVector);
		Vector3D operator* (Vector3D& rVector) const;

		void operator*= (float rScalar);
		Vector3D operator* (float rScalar) const;

		void operator/= (float rScalar);

		void operator-= (Vector3D& rVector);
		Vector3D operator- (Vector3D& rVector) const;

		void operator+= (Vector3D& rVector);
		Vector3D operator+ (Vector3D& rVector) const;

		void operator= (float rScalar);

		void Set(float _x, float _y, float _z);

		void Normilize();
		float Length() const;
		Vector3D CrossProduct(const Vector3D& rOther) const;
		float DotProduct(const Vector3D& rOther) const;

		float x = 0;
		float y = 0;
		float z = 0;

		static const Vector3D& Zero;
	};
}