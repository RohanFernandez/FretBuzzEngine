#pragma once
#include "transform.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		Transform::Transform(glm::vec3 a_v3Position, glm::vec3 a_v3Rotation, glm::vec3 a_v3Scale, Transform* a_pParentTransform)
			: m_pParentTransform{ a_pParentTransform }
		{
			setLocalRotation(a_v3Rotation);
			setLocalScale(a_v3Scale);
			setLocalPosition(a_v3Position);
			m_mat4Transformation = getTransformationMatrix();
		}

		Transform::Transform()
			: Transform({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, nullptr)
		{

		}

		Transform::~Transform()
		{
		
		}

		void Transform::setLocalRotation(glm::vec3 a_v3AngleInRadians)
		{
			glm::quat l_quatOld = m_quatRotation;
			m_quatRotation = glm::quat(a_v3AngleInRadians);

			m_bIsDirty = 
				(l_quatOld.x != m_quatRotation.x ||
				l_quatOld.y != m_quatRotation.y ||
				l_quatOld.z != m_quatRotation.z ||
				l_quatOld.w != m_quatRotation.w ||
					m_bIsDirty);

			if (m_bIsDirty)
			{
				glm::mat4 l_mat4Model{ m_quatRotation };
				m_v3Forward = glm::normalize(l_mat4Model * glm::vec4{ 0.0f, 0.0f, 1.0f, 0.0f });
				m_v3Up = glm::normalize(l_mat4Model * glm::vec4{ 0.0f, 1.0f, 0.0f, 0.0f });
				m_v3Right = glm::normalize(l_mat4Model * glm::vec4{ 1.0f, 0.0f, 0.0f, 0.0f });
			}
		}

		void Transform::setLocalScale(glm::vec3 a_v3Scale)
		{
			glm::vec3 l_v3OldScale = m_v3Scale;
			m_v3Scale = a_v3Scale;

			m_bIsDirty = (l_v3OldScale != m_v3Scale) || m_bIsDirty;
		}

		void Transform::setLocalPosition(glm::vec3 a_v3Position)
		{
			glm::vec3 l_v3OldPosition = m_v3Scale;
			m_v3Position = a_v3Position;
			
			m_bIsDirty = (l_v3OldPosition != m_v3Position) || m_bIsDirty;
		}

		void Transform::setWorldPosition(glm::vec3 a_v3Position)
		{
			glm::vec3 l_v3OldPosition = getWorldPosition();
			m_bIsDirty = (l_v3OldPosition != a_v3Position) || m_bIsDirty;

			if (m_bIsDirty)
			{
				m_v3Position += a_v3Position - l_v3OldPosition;
			}
		}

		glm::vec3 Transform::getWorldPosition() const
		{
			return (m_pParentTransform == nullptr) ? 
				m_v3Position : 
				m_pParentTransform->getTransformationMatrix() * glm::vec4(m_v3Position,1.0f);
		}

		glm::mat4 Transform::getModelMatrix()
		{
			glm::mat4 l_mat4Model = glm::mat4{ 1.0f };
			l_mat4Model = glm::translate(l_mat4Model, glm::vec3(m_v3Position));
			l_mat4Model = glm::scale(l_mat4Model, glm::vec3(m_v3Scale));
			l_mat4Model *= glm::mat4(m_quatRotation);

			return l_mat4Model;
		}

		glm::mat4 Transform::getTransformationMatrix()
		{
			if (m_pParentTransform == nullptr)
			{
				return getModelMatrix();
			}

			if (m_pParentTransform->m_bIsDirty)
			{
				m_pParentTransform->m_bIsDirty = false;
				m_pParentTransform->m_mat4Transformation = m_pParentTransform->getTransformationMatrix();
			}

			return m_pParentTransform->m_mat4Transformation * getModelMatrix();
		}
	}
}