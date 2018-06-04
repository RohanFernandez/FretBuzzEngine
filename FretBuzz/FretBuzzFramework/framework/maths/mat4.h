#pragma once
#include <iostream>
#include "vec3.h"
#include "vec4.h"
#include <array>

namespace ns_fretBuzz
{
	namespace ns_maths
	{
		struct mat4
		{
			static constexpr int MAX_MAT4_VALUES = 16;
			static constexpr int SIZE_OF_MAT4_ARRAY = sizeof(float) * MAX_MAT4_VALUES;

			union
			{
				float m_arrMat4[MAX_MAT4_VALUES];
				vec4 m_Vec4[4];
			};

			mat4(const float a_fDiagonal = 0.0f);
			mat4(float a_mat4Array[]);

			void operator=(const mat4& a_mat4);

			static mat4 identity();
			static mat4 orthographic(float a_fLeft, float a_fRight, float a_fBottom, float a_fTop, float a_fNear, float a_fFar);
			static mat4 perspective(float a_fNear, float a_fFar, float a_fAspect, float a_fDegreesFOV);

			mat4& multiply(const mat4& a_mat4); 
			mat4& operator*=(const mat4& a_mat4);
			friend mat4 operator*(mat4 a_mat4left, const mat4& a_mat4Right);

			vec3 multiply(const vec3& a_vec3) const;
			vec3 operator*(const vec3& a_vec3) const;

			vec4 multiply(const vec4& a_vec4) const;
			vec4 operator*(const vec4& a_vec4) const;

			static mat4 translate(const vec3& a_vec3);
			static mat4 translate(const float x, const float y, const float z);

			static mat4 scale(const vec3& a_vec3);
			static mat4 scale(const float x, const float y, const float z);

			static mat4 rotate(const float a_fDegree, vec3 a_v3Axis);

			friend std::ostream& operator<<(std::ostream& a_ostream, const mat4& a_mat4);
		};
	}
}