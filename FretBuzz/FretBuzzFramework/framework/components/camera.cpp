#pragma once
#include "camera.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		Camera::Camera(glm::vec3 a_v3Pos, glm::vec3 a_v3Rotation, glm::vec3 a_v3Scale, PROJECTION_TYPE a_ProjectionType, glm::mat4 a_mat4Projection)
			: m_mat4Projection{ a_mat4Projection },
			m_ProjectionType{ a_ProjectionType },
			m_transform(a_v3Pos, a_v3Rotation,a_v3Scale)
		{
			updateViewMatrix();
		}

		const glm::mat4& Camera::updateViewMatrix()
		{
			m_mat4View = glm::lookAt(m_transform.getPosition(), m_transform.getPosition() + m_transform.getForward(), m_transform.getUp());
			return m_mat4View;
		}
	}
}