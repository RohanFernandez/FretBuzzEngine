#pragma once
#include "components/rect_transform.h"
#include "game_object.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		class  GameObject2D : public GameObject
		{
		protected:
			GameObject2D(GameObject& a_ParentGameObject, std::string a_strName, glm::vec3 a_v3Position, glm::vec3 a_v3Rotation, glm::vec3 a_v3Scale, glm::vec2 a_v2DimensionWH, char* a_Layer = LayerManager::LAYER_NAME_DEFAULT, bool a_bIsActiveSelf = true);
			virtual ~GameObject2D();

			RectTransform* m_pRectTransform = nullptr;

			virtual void editorTransformRender() override;

		public:
			static GameObject2D* instantiate(GameObject& a_ParentGameObject, std::string a_strName, glm::vec3 a_v3Position, glm::vec3 a_v3Rotation, glm::vec3 a_v3Scale, glm::vec2 a_v2DimensionWH, char* a_Layer = LayerManager::LAYER_NAME_DEFAULT, bool a_bIsActiveSelf = true);

			RectTransform& m_RectTransform;

			//Adds a component of the given type to this gameobject
			template<typename T_COMPONENT_TYPE, typename ...T_ARGS, typename = typename std::enable_if<std::is_base_of<IComponent, T_COMPONENT_TYPE>::value>::type>
			T_COMPONENT_TYPE* addComponent(T_ARGS... a_Args)
			{
				T_COMPONENT_TYPE* l_pNewComponent = new T_COMPONENT_TYPE(this, a_Args...);
				IComponent* l_pIComponent = static_cast<T_COMPONENT_TYPE*>(l_pNewComponent);
				GameObject::addComponent(l_pIComponent);
				GameObject::onComponentCreated(l_pIComponent);
				return l_pNewComponent;
			}
		};
	}
}