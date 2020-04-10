#pragma once
#include "components/rect_transform.h"
#include "game_object.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		class FRETBUZZ_API GameObject2D : public GameObject
		{
		protected:
			GameObject2D(GameObject& a_ParentGameObject, std::string a_strName, glm::vec3 a_v3Position, glm::vec3 a_v3Rotation, glm::vec3 a_v3Scale, glm::vec2 a_v2DimensionWH, Layer a_Layer, bool a_bIsActiveSelf);
			virtual ~GameObject2D();

			RectTransform* m_pRectTransform = nullptr;

		public:
			static GameObject2D* instantiate(GameObject& a_ParentGameObject, std::string a_strName, glm::vec3 a_v3Position, glm::vec3 a_v3Rotation, glm::vec3 a_v3Scale, glm::vec2 a_v2DimensionWH, Layer a_Layer, bool a_bIsActiveSelf = true);

			RectTransform& m_RectTransform;
		};
	}
}