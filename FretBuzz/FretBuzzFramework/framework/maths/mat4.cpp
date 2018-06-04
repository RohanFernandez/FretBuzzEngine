#pragma once
#include "mat4.h"
#include "math_utils.h"

namespace ns_fretBuzz
{
	namespace ns_maths
	{	
		mat4::mat4(const float a_fDiagonal)
			: m_arrMat4{ a_fDiagonal }
		{
			m_arrMat4[0] = a_fDiagonal;
			m_arrMat4[5] = a_fDiagonal;
			m_arrMat4[10] = a_fDiagonal;
			m_arrMat4[15] = a_fDiagonal;
		}

		mat4::mat4(float a_mat4Array[])
			: m_arrMat4{ }
		{
			std::memcpy(m_arrMat4, a_mat4Array, 16 * sizeof(int));
		}

		void mat4::operator=(const mat4& a_mat4)
		{
			std::memcpy(m_arrMat4, a_mat4.m_arrMat4, SIZE_OF_MAT4_ARRAY);
		}

		mat4 mat4::identity()
		{
			return mat4(1.0f);
		}

		mat4 mat4::orthographic(float a_fLeft, float a_fRight, float a_fBottom, float a_fTop, float a_fNear, float a_fFar)
		{
			mat4 l_return(1.0f);

			l_return.m_arrMat4[0]  = 2.0f / (a_fRight - a_fLeft);
			l_return.m_arrMat4[5]  = 2.0f / (a_fTop - a_fBottom);
			l_return.m_arrMat4[10] = 2.0f / (a_fNear - a_fFar);

			l_return.m_arrMat4[12] = (a_fLeft + a_fRight) / (a_fLeft - a_fRight);
			l_return.m_arrMat4[13] = (a_fBottom + a_fTop) / (a_fBottom - a_fTop);
			l_return.m_arrMat4[14] = (a_fFar + a_fNear) / (a_fFar - a_fNear);

			return l_return;
		}

		mat4 mat4::perspective(float a_fNear, float a_fFar, float a_fAspect, float a_fDegreesFOV)
		{
			mat4 l_return(1.0f);

			float q = 1.0f / (float)tan(MathUtils::toRadians(a_fDegreesFOV * 0.5f));
			float a = q / a_fAspect;
			float b = (a_fNear + a_fFar) / (a_fNear - a_fFar);
			float c = (2.0f * a_fNear * a_fFar) / (a_fNear - a_fFar);

			l_return.m_arrMat4[0 + 0 * 4] = a;
			l_return.m_arrMat4[1 + 1 * 4] = q;
			l_return.m_arrMat4[2 + 2 * 4] = b;
			l_return.m_arrMat4[3 + 2 * 4] = -1.0f;
			l_return.m_arrMat4[2 + 3 * 4] = c;

			return l_return;
		}

		mat4& mat4::multiply(const mat4& a_mat4)
		{
			mat4 l_newMat4;

			for (int l_iLeftCol = 0; l_iLeftCol < 4; l_iLeftCol++)
			{
				for (int l_iRightRow = 0; l_iRightRow < 4; l_iRightRow++)
				{
					float l_fCurrSum = 0.0f;
					for (int l_iIndex = 0; l_iIndex < 4; l_iIndex++)
					{
						l_fCurrSum += m_arrMat4[l_iIndex + l_iLeftCol * 4] * a_mat4.m_arrMat4[l_iRightRow + l_iIndex * 4];
					}
					l_newMat4.m_arrMat4[l_iRightRow + l_iLeftCol * 4] = l_fCurrSum;
				}
			}
			*this = l_newMat4;
			return *this;
		}

		mat4& mat4::operator*=(const mat4& a_mat4)
		{
			return multiply(a_mat4);
		}

		mat4 operator*(mat4 a_mat4left, const mat4& a_mat4Right)
		{
			return a_mat4left.multiply(a_mat4Right);
		}

		vec3 mat4::multiply(const vec3& a_vec3) const
		{
			vec3 l_return;
			l_return.x = m_arrMat4[0] * a_vec3.x + m_arrMat4[4] * a_vec3.y + m_arrMat4[8] * a_vec3.z + m_arrMat4[12];
			l_return.y = m_arrMat4[1] * a_vec3.x + m_arrMat4[5] * a_vec3.y + m_arrMat4[9] * a_vec3.z + m_arrMat4[13];
			l_return.z = m_arrMat4[2] * a_vec3.x + m_arrMat4[6] * a_vec3.y + m_arrMat4[10] * a_vec3.z + m_arrMat4[14];
			return l_return;
		}

		vec3 mat4::operator*(const vec3& a_vec3) const
		{
			return multiply(a_vec3);
		}

		vec4 mat4::multiply(const vec4& a_vec4) const
		{
			vec4 l_return;
			l_return.x = m_arrMat4[0] * a_vec4.x + m_arrMat4[4] * a_vec4.y + m_arrMat4[8] * a_vec4.z + m_arrMat4[12] * a_vec4.w;
			l_return.y = m_arrMat4[1] * a_vec4.x + m_arrMat4[5] * a_vec4.y + m_arrMat4[9] * a_vec4.z + m_arrMat4[13] * a_vec4.w;
			l_return.z = m_arrMat4[2] * a_vec4.x + m_arrMat4[6] * a_vec4.y + m_arrMat4[10] * a_vec4.z + m_arrMat4[14] * a_vec4.w;
			l_return.w = m_arrMat4[3] * a_vec4.x + m_arrMat4[7] * a_vec4.y + m_arrMat4[11] * a_vec4.z + m_arrMat4[15] * a_vec4.w;

			return l_return;
		}

		vec4 mat4::operator*(const vec4& a_vec4) const
		{
			return multiply(a_vec4);
		}

		mat4 mat4::translate(const vec3& a_vec3)
		{
			mat4 l_return(1.0f);
			l_return.m_arrMat4[12] = a_vec3.x;
			l_return.m_arrMat4[13] = a_vec3.y;
			l_return.m_arrMat4[14] = a_vec3.z;
			return l_return;
		}

		mat4 mat4::translate(const float x, const float y, const float z)
		{
			return translate({ x, y, z });
		}

		mat4 mat4::scale(const vec3& a_vec3)
		{
			mat4 l_return(1.0f);
			l_return.m_arrMat4[0] = a_vec3.x;
			l_return.m_arrMat4[5] = a_vec3.y;
			l_return.m_arrMat4[10] = a_vec3.z;
			return l_return;
		}

		mat4 mat4::scale(const float x, const float y, const float z)
		{
			return scale({ x, y, z });
		}

		mat4 mat4::rotate(const float a_fDegree, vec3 a_v3Axis)
		{
			mat4 result = identity();
			float r = MathUtils::toRadians(a_fDegree);
			float c = cos(r);
			float s = sin(r);
			float omc = 1.0f - c;

			float x = a_v3Axis.x;
			float y = a_v3Axis.y;
			float z = a_v3Axis.z;

			result.m_arrMat4[0] = x * omc + c;
			result.m_arrMat4[1] = y * x * omc + z * s;
			result.m_arrMat4[2] = x * z * omc - y * s;
				   
			result.m_arrMat4[4] = x * y * omc - z * s;
			result.m_arrMat4[5] = y * omc + c;
			result.m_arrMat4[6] = y * z * omc + x * s;
				   
			result.m_arrMat4[8] = x * z * omc + y * s;
			result.m_arrMat4[9] = y * z * omc - x * s;
			result.m_arrMat4[10] = z * omc + c;

			return result;
		}

		std::ostream& operator<<(std::ostream& a_ostream, const mat4& a_mat4)
		{
			a_ostream << "{ ";
			for (int l_iMat4Index = 0; l_iMat4Index < mat4::MAX_MAT4_VALUES; l_iMat4Index++)
			{
				a_ostream << a_mat4.m_arrMat4[l_iMat4Index] << "  ";
			}
			a_ostream << " }";
			return a_ostream;
		}
	}
}