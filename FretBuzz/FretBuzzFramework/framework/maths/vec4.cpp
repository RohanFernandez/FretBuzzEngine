#pragma once
#include "vec4.h"

namespace ns_fretBuzz
{
	namespace ns_maths
	{
		vec4::vec4()
		{

		}

		vec4::vec4(float a_fX, float a_fY, float a_fZ, float a_fW)
			: x{ a_fX },
			  y{ a_fY },
			  z{ a_fZ },
			  w{ a_fW }
		{

		}

		vec4& vec4::add(const vec4& a_vec4)
		{
			x += a_vec4.x;
			y += a_vec4.y;
			z += a_vec4.z;
			w += a_vec4.w;
			return *this;
		}

		vec4& vec4::subtract(const vec4& a_vec4)
		{
			x -= a_vec4.x;
			y -= a_vec4.y;
			z -= a_vec4.z;
			w -= a_vec4.w;
			return *this;
		}

		vec4& vec4::multiply(const vec4& a_vec4)
		{
			x *= a_vec4.x;
			y *= a_vec4.y;
			z *= a_vec4.z;
			w *= a_vec4.w;
			return *this;
		}

		vec4& vec4::divide(const vec4& a_vec4)
		{
			x /= a_vec4.x;
			y /= a_vec4.y;
			z /= a_vec4.z;
			w /= a_vec4.w;
			return *this;
		}

		vec4 operator+(vec4 a_left, const vec4& a_right)
		{
			return a_left.add(a_right);
		}

		vec4 operator-(vec4 a_left, const vec4& a_right)
		{
			return a_left.subtract(a_right);
		}

		vec4 operator*(vec4 a_left, const vec4& a_right)
		{
			return a_left.multiply(a_right);
		}

		vec4 operator/(vec4 a_left, const vec4& a_right)
		{
			return a_left.divide(a_right);
		}

		vec4& vec4::operator+=(const vec4& a_vec4)
		{
			return add(a_vec4);
		}

		vec4& vec4::operator-=(const vec4& a_vec4)
		{
			return subtract(a_vec4);
		}

		vec4& vec4::operator*=(const vec4& a_vec4)
		{
			return multiply(a_vec4);
		}

		vec4& vec4::operator/=(const vec4& a_vec4)
		{
			return divide(a_vec4);
		}

		void vec4::operator=(const vec4& a_vec4)
		{
			x = a_vec4.x;
			y = a_vec4.y;
			z = a_vec4.z;
			w = a_vec4.w;
		}

		bool operator==(const vec4& a_left, const vec4& a_right)
		{
			return a_left.x == a_right.x && a_left.y == a_right.y && a_left.z == a_right.z && a_left.w == a_right.w;
		}

		bool operator!=(const vec4& a_left, const vec4& a_right)
		{
			return !(a_left == a_right);
		}

		std::ostream& operator<<(std::ostream& a_OStream, const vec4& a_vec4)
		{
			return a_OStream << "(" << a_vec4.x << "," << a_vec4.y << a_vec4.z << "," << a_vec4.w << ")";
		}
	}
}