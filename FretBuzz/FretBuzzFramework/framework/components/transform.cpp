#pragma once
#include "transform.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		Transform::Transform(glm::vec3 a_v3Position, glm::vec3 a_v3Rotation, glm::vec3 a_v3Scale)
			:  
			m_v3Position{ a_v3Position },
			m_v3Rotation{ a_v3Rotation },
			m_v3Scale{ a_v3Scale },
			m_v3Forward{ 0.0f, 0.0f, 1.0f },
			m_v3Up{ 0.0f, 1.0f, 0.0f },
			m_v3Right {1.0f, 0.0f, 0.0f}
		{
			rotate(m_v3Rotation);
			scale(m_v3Scale);
			translate(m_v3Position);
		}

		Transform::Transform()
			: Transform({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, {1.0f, 1.0f, 1.0f})
		{
			
		}

		Transform::~Transform()
		{
		
		}

		void Transform::rotate(glm::vec3 a_v3AngleInRadians)
		{
			m_v3Rotation = a_v3AngleInRadians;
			glm::mat4 l_mat4Model{ 1.0f };
			l_mat4Model = glm::rotate(l_mat4Model, m_v3Rotation.x, { 1.0f, 0.0f, 0.0f });
			l_mat4Model = glm::rotate(l_mat4Model, m_v3Rotation.y, { 0.0f, 1.0f, 0.0f });
			l_mat4Model = glm::rotate(l_mat4Model, m_v3Rotation.z, { 0.0f, 0.0f, 1.0f });

			m_v3Forward = glm::normalize(l_mat4Model * glm::vec4{ 0.0f, 0.0f, 1.0f, 0.0f });
			m_v3Up = glm::normalize(l_mat4Model * glm::vec4{ 0.0f, 1.0f, 0.0f, 0.0f });
			m_v3Right = glm::normalize(l_mat4Model * glm::vec4{ 1.0f, 0.0f, 0.0f, 0.0f });
		}

		void Transform::scale(glm::vec3 a_v3Scale)
		{
			m_v3Scale = a_v3Scale;
		}

		void Transform::translate(glm::vec3 a_v3Translate)
		{
			m_v3Position = a_v3Translate;
		}

		const glm::mat4 Transform::getModelMatrix()
		{
			glm::mat4 l_mat4Model{ 1.0f };

			l_mat4Model = glm::translate(l_mat4Model, glm::vec3(m_v3Position));
			l_mat4Model = glm::scale(l_mat4Model, glm::vec3(m_v3Scale));
			l_mat4Model = glm::rotate(l_mat4Model, m_v3Rotation.z, { 0.0f, 0.0f, 1.0f });
			l_mat4Model = glm::rotate(l_mat4Model, m_v3Rotation.y, { 0.0f, 1.0f, 0.0f });
			l_mat4Model = glm::rotate(l_mat4Model, m_v3Rotation.x, { 1.0f, 0.0f, 0.0f });

			return l_mat4Model;
		}
	}
}