#pragma once
#include "math_utils.h"
#include <cmath>

namespace ns_fretBuzz
{
	namespace ns_maths
	{
		float MathUtils::toRadians(float a_fDegree)
		{
			return (a_fDegree / 180.0f) * (float)M_PI;
		}	 
	}
}