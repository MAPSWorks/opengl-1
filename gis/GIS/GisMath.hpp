#pragma once
#include "glm/gtc/matrix_transform.hpp"
namespace GIS
{
	class float2
	{
	protected:
		float _x;
		float _y;
	public:
		float2(float x, float y)
		{
			_x = x;
			_y = y;
		}
	};

	class Rgba4Byte
	{
	public:
		unsigned char _r;
		unsigned char _g;
		unsigned char _b;
		unsigned char _a;
	public:
		Rgba4Byte(
			unsigned char r = 255,
			unsigned char g = 255,
			unsigned char b = 255,
			unsigned char a = 255
		)
		{
			_r = r;
			_g = g;
			_b = b;
			_a = a;
		}
	};
	typedef Rgba4Byte	Rgba;
}