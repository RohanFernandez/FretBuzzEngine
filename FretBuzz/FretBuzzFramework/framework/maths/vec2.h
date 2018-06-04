#pragma once
#include <iostream>

namespace ns_fretBuzz
{
	namespace ns_maths
	{
		struct vec2
		{
			float x = 0.0f;
			float y = 0.0f;

			vec2();
			vec2(float a_fX, float a_fY);

			vec2& add(const vec2& a_vec2);
			vec2& subtract(const vec2& a_vec2);
			vec2& multiply(const vec2& a_vec2);
			vec2& divide(const vec2& a_vec2);

			friend vec2 operator+(vec2 left, const vec2& a_right);
			friend vec2 operator-(vec2 left, const vec2& a_right);
			friend vec2 operator*(vec2 left, const vec2& a_right);
			friend vec2 operator/(vec2 left, const vec2& a_right);

			vec2& operator+=(const vec2& a_vec2);
			vec2& operator-=(const vec2& a_vec2);
			vec2& operator*=(const vec2& a_vec2);
			vec2& operator/=(const vec2& a_vec2);

			void operator=(const vec2& a_vec2);
			friend bool operator==(const vec2& left, const vec2& a_right);
			friend bool operator!=(const vec2& left, const vec2& a_right);
			friend std::ostream& operator<<(std::ostream& a_OStream, const vec2& a_Vec2);
		};
	}
}