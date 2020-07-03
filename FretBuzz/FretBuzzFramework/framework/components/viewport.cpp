#include <fretbuzz_pch.h>
#include "viewport.h"

namespace ns_fretBuzz
{
	Viewport::Viewport(PROJECTION_TYPE a_ProjectionType, glm::mat4 a_mat4Projection, glm::vec2 a_v2OriginXY01, glm::vec2 a_v2DimensionWH01)
		: m_mat4Projection{ a_mat4Projection },
		m_mat4View{1.0f},
		m_ProjectionType{ a_ProjectionType },
		m_v2OriginXY01{ a_v2OriginXY01 },
		m_v2DimensionWH01{ a_v2DimensionWH01 }
	{
	}
}