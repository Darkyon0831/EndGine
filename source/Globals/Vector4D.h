#pragma once

namespace EG
{
	class Vector2D;

	class Vector4D
	{
	public:

		Vector4D() = default;
		Vector4D(float x, float y);

		void operator*= (Vector4D& rVector);
		Vector4D operator* (Vector4D& rVector) const;

		void operator-= (Vector4D& rVector);
		Vector4D operator- (Vector4D& rVector) const;

		void operator+= (Vector4D& rVector);
		Vector4D operator+ (Vector4D& rVector) const;

		float x = 0;
		float y = 0;
		float z = 0;
		float w = 0;
	};
}