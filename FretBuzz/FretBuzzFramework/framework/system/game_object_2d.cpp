#pragma once
#include "game_object_2d.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		GameObject2D::GameObject2D(GameObject& a_ParentGameObject, std::string a_strName, glm::vec3 a_v3Position, glm::vec3 a_v3Rotation, glm::vec3 a_v3Scale, glm::vec2 a_v2DimensionWH, bool a_bIsActiveSelf)
			: 
			GameObject(a_ParentGameObject, a_strName, a_v3Position,  a_v3Rotation, a_v3Scale, 
				new RectTransform(a_v3Position, a_v3Rotation, a_v3Scale, a_v2DimensionWH, &a_ParentGameObject.m_Transform), a_bIsActiveSelf),
			m_pRectTransform{ dynamic_cast<RectTransform*>(m_pTransform)},
			m_RectTransform{ *m_pRectTransform }
		{
		
		}

		GameObject2D:: ~GameObject2D()
		{
		}

		GameObject2D* GameObject2D::instantiate(GameObject& a_ParentGameObject, std::string a_strName, glm::vec3 a_v3Position, glm::vec3 a_v3Rotation, glm::vec3 a_v3Scale, glm::vec2 a_v2DimensionWH, bool a_bIsActiveSelf)
		{
			return new GameObject2D(a_ParentGameObject, a_strName, a_v3Position, a_v3Rotation, a_v3Scale, a_v2DimensionWH, a_bIsActiveSelf);
		}
	}
}