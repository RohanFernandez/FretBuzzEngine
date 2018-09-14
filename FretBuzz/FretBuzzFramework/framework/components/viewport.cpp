#pragma once
#include "viewport.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		Viewport::Viewport(PROJECTION_TYPE a_ProjectionType, glm::mat4 a_mat4Projection)
			: m_mat4Projection{ a_mat4Projection },
			m_ProjectionType{ a_ProjectionType }
		{
		}
	}
}