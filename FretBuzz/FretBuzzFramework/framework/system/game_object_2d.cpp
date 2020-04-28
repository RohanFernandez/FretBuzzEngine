#include <fretbuzz_pch.h>
#include "game_object_2d.h"
#include <imgui/imgui.h>

namespace ns_fretBuzz
{
	namespace ns_system
	{
		GameObject2D::GameObject2D(GameObject& a_ParentGameObject, std::string a_strName, glm::vec3 a_v3Position, glm::vec3 a_v3Rotation, glm::vec3 a_v3Scale, glm::vec2 a_v2DimensionWH, Layer a_Layer, bool a_bIsActiveSelf)
			: 
			GameObject(a_ParentGameObject, a_strName, a_v3Position,  a_v3Rotation, a_v3Scale, 
				new RectTransform(a_v3Position, a_v3Rotation, a_v3Scale, a_v2DimensionWH, &a_ParentGameObject.m_Transform), a_Layer, a_bIsActiveSelf),
			m_pRectTransform{ dynamic_cast<RectTransform*>(m_pTransform)},
			m_RectTransform{ *m_pRectTransform }
		{
		
		}

		GameObject2D:: ~GameObject2D()
		{
		}

		void GameObject2D::editorTransformRender()
		{
			ImGui::Text("Dimension "); ImGui::SameLine(100);

			float l_arrDimension[2] = { m_RectTransform.m_Rect.m_v2DimensionsWH.x, m_RectTransform.m_Rect.m_v2DimensionsWH.y };

			if (ImGui::InputFloat2("##Dimension", l_arrDimension, 2))
			{
				m_RectTransform.m_Rect.reset({ l_arrDimension[0], l_arrDimension[1] });
			}

			GameObject::editorTransformRender();
		}

		GameObject2D* GameObject2D::instantiate(GameObject& a_ParentGameObject, std::string a_strName, glm::vec3 a_v3Position, glm::vec3 a_v3Rotation, glm::vec3 a_v3Scale, glm::vec2 a_v2DimensionWH, Layer a_Layer, bool a_bIsActiveSelf)
		{
			return new GameObject2D(a_ParentGameObject, a_strName, a_v3Position, a_v3Rotation, a_v3Scale, a_v2DimensionWH, a_Layer, a_bIsActiveSelf);
		}
	}
}