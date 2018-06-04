#pragma once
#include <iostream>

namespace ns_fretBuzz
{
	namespace ns_maths
	{
		struct vec3
		{
			float x = 0.0f;
			float y = 0.0f;
			float z = 0.0f;

			vec3();
			vec3(float a_fX, float a_fY, float a_fZ);

			vec3& add(const vec3& a_vec3);
			vec3& subtract(const vec3& a_vec3);
			vec3& multiply(const vec3& a_vec3);
			vec3& divide(const vec3& a_vec3);

			friend vec3 operator+(vec3 left, const vec3& a_right);
			friend vec3 operator-(vec3 left, const vec3& a_right);
			friend vec3 operator*(vec3 left, const vec3& a_right);
			friend vec3 operator/(vec3 left, const vec3& a_right);

			vec3& operator+=(const vec3& a_vec3);
			vec3& operator-=(const vec3& a_vec3);
			vec3& operator*=(const vec3& a_vec3);
			vec3& operator/=(const vec3& a_vec3);

			vec3 operator*(const float a_fScalar);

			void operator=(const vec3& a_vec3);
			friend bool operator==(const vec3& left, const vec3& a_right);
			friend bool operator!=(const vec3& left, const vec3& a_right);
			friend std::ostream& operator<<(std::ostream& a_OStream, const vec3& a_vec3);

			vec3 normalize() const;
			float magnitude() const;

			vec3 cross(const vec3& a_v3Right) const;
			float dot(const vec3& a_v3Right) const;
		};
	}
}