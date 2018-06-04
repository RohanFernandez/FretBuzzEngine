#pragma once
#include <iostream>

namespace ns_fretBuzz
{
	namespace ns_maths
	{
		struct vec4
		{
			float x = 0.0f;
			float y = 0.0f;
			float z = 0.0f;
			float w = 0.0f;

			vec4();
			vec4(float a_fX, float a_fY, float a_fZ, float a_fW);

			vec4& add(const vec4& a_vec4);
			vec4& subtract(const vec4& a_vec4);
			vec4& multiply(const vec4& a_vec4);
			vec4& divide(const vec4& a_vec4);

			friend vec4 operator+(vec4 left, const vec4& a_right);
			friend vec4 operator-(vec4 left, const vec4& a_right);
			friend vec4 operator*(vec4 left, const vec4& a_right);
			friend vec4 operator/(vec4 left, const vec4& a_right);

			vec4& operator+=(const vec4& a_vec4);
			vec4& operator-=(const vec4& a_vec4);
			vec4& operator*=(const vec4& a_vec4);
			vec4& operator/=(const vec4& a_vec4);

			void operator=(const vec4& a_vec4);
			friend bool operator==(const vec4& left, const vec4& a_right);
			friend bool operator!=(const vec4& left, const vec4& a_right);
			friend std::ostream& operator<<(std::ostream& a_OStream, const vec4& a_vec4);
		};
	}
}