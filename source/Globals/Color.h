#pragma once

namespace EG
{
	class Color
	{
	public:
		Color();
		Color(float _r, float _g, float _b, float _a = 1.0f);
		
		float r;
		float g;
		float b;
		float a;
	};
}