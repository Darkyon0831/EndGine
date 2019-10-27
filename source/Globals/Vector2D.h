#pragma once

namespace EG
{
	class Vector2D
	{
	public:

		Vector2D() = default;
		Vector2D(float x, float y);

		void operator*= (Vector2D& rVector);
		Vector2D operator* (Vector2D& rVector) const;

		void operator-= (Vector2D& rVector);
		Vector2D operator- (Vector2D& rVector) const;

		void operator+= (Vector2D& rVector);
		Vector2D operator+ (Vector2D& rVector) const;

		float x = 0;
		float y = 0;
	};
}