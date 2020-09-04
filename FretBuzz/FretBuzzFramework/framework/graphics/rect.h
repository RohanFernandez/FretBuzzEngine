#pragma once

namespace FRETBUZZ
{
	struct  Rect
	{

		glm::vec2 m_v2DimensionsWH = {0.0f, 0.0f};
		std::vector<glm::vec4> m_VertPosition;
		
		Rect()
		{}

		Rect(glm::vec2 a_v2DimensionsWH)
			: m_v2DimensionsWH{a_v2DimensionsWH}
		{
			m_VertPosition.resize(4);
			reset(a_v2DimensionsWH);
		}

		~Rect()
		{}

		void reset(glm::vec2 a_v2DimensionWH)
		{
			m_v2DimensionsWH = a_v2DimensionWH;
			m_VertPosition[0] = { m_v2DimensionsWH.x * -0.5, m_v2DimensionsWH.y * -0.5, 0.0f, 1.0f };
			m_VertPosition[1] = { m_v2DimensionsWH.x * -0.5, m_v2DimensionsWH.y *  0.5, 0.0f, 1.0f };
			m_VertPosition[2] = { m_v2DimensionsWH.x *  0.5, m_v2DimensionsWH.y *  0.5, 0.0f, 1.0f };
			m_VertPosition[3] = { m_v2DimensionsWH.x *  0.5, m_v2DimensionsWH.y * -0.5, 0.0f, 1.0f };
		}
	};
}