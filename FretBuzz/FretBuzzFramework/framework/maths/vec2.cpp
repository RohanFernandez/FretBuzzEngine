#pragma once
#include "vec2.h"

namespace ns_fretBuzz
{
	namespace ns_maths
	{
		vec2::vec2()
		{

		}

		vec2::vec2(float a_fX, float a_fY)
			: x{ a_fX },
			  y{ a_fY }
		{

		}

		vec2& vec2::add(const vec2& a_vec2)
		{
			x += a_vec2.x;
			y += a_vec2.y;
			return *this;
		}

		vec2& vec2::subtract(const vec2& a_vec2)
		{
			x -= a_vec2.x;
			y -= a_vec2.y;
			return *this;
		}

		vec2& vec2::multiply(const vec2& a_vec2)
		{
			x *= a_vec2.x;
			y *= a_vec2.y;
			return *this;
		}

		vec2& vec2::divide(const vec2& a_vec2)
		{
			x /= a_vec2.x;
			y /= a_vec2.y;
			return *this;
		}

		vec2 operator+(vec2 a_left, const vec2& a_right)
		{
			return a_left.add(a_right);
		}

		vec2 operator-(vec2 a_left, const vec2& a_right)
		{
			return a_left.subtract(a_right);
		}

		vec2 operator*(vec2 a_left, const vec2& a_right)
		{
			return a_left.multiply(a_right);
		}

		vec2 operator/(vec2 a_left, const vec2& a_right)
		{
			return a_left.divide(a_right);
		}

		vec2& vec2::operator+=(const vec2& a_vec2)
		{
			return add(a_vec2);
		}

		vec2& vec2::operator-=(const vec2& a_vec2)
		{
			return subtract(a_vec2);
		}

		vec2& vec2::operator*=(const vec2& a_vec2)
		{
			return multiply(a_vec2);
		}

		vec2& vec2::operator/=(const vec2& a_vec2)
		{
			return divide(a_vec2);
		}

		void vec2::operator=(const vec2& a_vec2)
		{
			x = a_vec2.x;
			y = a_vec2.y;
		}

		bool operator==(const vec2& a_left, const vec2& a_right)
		{
			return a_left.x == a_right.x && a_left.y == a_right.y;
		}

		bool operator!=(const vec2& a_left, const vec2& a_right)
		{
			return !(a_left == a_right);
		}

		std::ostream& operator<<(std::ostream& a_OStream, const vec2& a_Vec2)
		{
			return a_OStream << "(" << a_Vec2.x << "," << a_Vec2.y << ")";
		}
	}
}