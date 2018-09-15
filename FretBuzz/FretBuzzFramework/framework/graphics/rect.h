#pragma once
#include "../utils/math.h"

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		struct Rect
		{

		glm::vec2 m_v2DimensionsWH = {0.0f, 0.0f};
		glm::vec4 m_arrRect[4] = { glm::vec4{0.0f} };

		static constexpr int SIZE_OF_RECT_COORDINATES = sizeof(glm::vec4) * 4;
			
		Rect()
		{
			
		}

		Rect(glm::vec2 a_v2DimensionsWH, glm::vec4* a_pArrRect)
			: m_v2DimensionsWH{a_v2DimensionsWH}
		{
			memcpy(m_arrRect, a_pArrRect, SIZE_OF_RECT_COORDINATES);
		}

		~Rect() 
		{}

		};
	}
}