#pragma once
#include "vec3.h"

namespace ns_fretBuzz
{
	namespace ns_maths
	{
		vec3::vec3()
		{

		}

		vec3::vec3(float a_fX, float a_fY, float a_fZ)
			: x{ a_fX },
			  y{ a_fY },
			  z{ a_fZ }
		{

		}

		vec3& vec3::add(const vec3& a_vec3)
		{
			x += a_vec3.x;
			y += a_vec3.y;
			z += a_vec3.z;
			return *this;
		}

		vec3& vec3::subtract(const vec3& a_vec3)
		{
			x -= a_vec3.x;
			y -= a_vec3.y;
			z -= a_vec3.z;
			return *this;
		}

		vec3& vec3::multiply(const vec3& a_vec3)
		{
			x *= a_vec3.x;
			y *= a_vec3.y;
			z *= a_vec3.z;
			return *this;
		}

		vec3& vec3::divide(const vec3& a_vec3)
		{
			x /= a_vec3.x;
			y /= a_vec3.y;
			z /= a_vec3.z;
			return *this;
		}

		vec3 operator+(vec3 a_left, const vec3& a_right)
		{
			return a_left.add(a_right);
		}

		vec3 operator-(vec3 a_left, const vec3& a_right)
		{
			return a_left.subtract(a_right);
		}

		vec3 operator*(vec3 a_left, const vec3& a_right)
		{
			return a_left.multiply(a_right);
		}

		vec3 operator/(vec3 a_left, const vec3& a_right)
		{
			return a_left.divide(a_right);
		}

		vec3& vec3::operator+=(const vec3& a_vec3)
		{
			return add(a_vec3);
		}

		vec3& vec3::operator-=(const vec3& a_vec3)
		{
			return subtract(a_vec3);
		}

		vec3& vec3::operator*=(const vec3& a_vec3)
		{
			return multiply(a_vec3);
		}

		vec3& vec3::operator/=(const vec3& a_vec3)
		{
			return divide(a_vec3);
		}

		void vec3::operator=(const vec3& a_vec3)
		{
			x = a_vec3.x;
			y = a_vec3.y;
			z = a_vec3.z;
		}

		bool operator==(const vec3& a_left, const vec3& a_right)
		{
			return a_left.x == a_right.x && a_left.y == a_right.y && a_left.z == a_right.z;
		}

		bool operator!=(const vec3& a_left, const vec3& a_right)
		{
			return !(a_left == a_right);
		}

		std::ostream& operator<<(std::ostream& a_OStream, const vec3& a_vec3)
		{
			return a_OStream << "(" << a_vec3.x << "," << a_vec3.y <<","<< a_vec3.z <<")";
		}

		vec3 vec3::normalize() const
		{
			float l_fMagnitude = magnitude();
			return { x / l_fMagnitude, y / l_fMagnitude , z / l_fMagnitude };
		}

		float vec3::magnitude() const
		{
			return sqrt(x*x + y * y + z * z);
		}

		vec3 vec3 ::cross(const vec3& a_v3Right) const
		{
			
			return
			{
			y * a_v3Right.z - z * a_v3Right.y,
			z * a_v3Right.x - x * a_v3Right.z,
			x * a_v3Right.y - y * a_v3Right.x
			};
		}

		float vec3::dot(const vec3& a_v3Right) const
		{
			return { x * a_v3Right.x + y * a_v3Right.y + z * a_v3Right.z };
		}

		vec3 vec3::operator*(const float a_fScalar)
		{
			return { x * a_fScalar, y * a_fScalar, z * a_fScalar };
		}
	}
}