#pragma once

#include "../components/transform.h"
#include "component.h"
#include <vector>
#include <string>

namespace ns_fretBuzz
{
	namespace ns_system
	{
		class GameObject
		{
			friend class IScene;
			friend class IComponent;
		protected:
			std::vector<IComponent*> m_Components;
			std::vector<GameObject*> m_Children;
			bool m_bIsRoot = false;

			GameObject* m_pParentGameObject = nullptr;

			const std::string m_strName;
			const int m_iID;

			static int s_iID;

			bool m_bIsDontDestroy = false;

			bool m_bIsActiveSelf = true;
			bool m_bIsActiveInHierarchy = true;

			void setActiveInHierarchyRecursively(bool a_bIsActive);

			void updateComponents(float a_fDeltaTime);
			void updateChildren(float a_fDeltaTime);

			void renderComponents(const glm::mat4& a_mat4Transformation, const Viewport& a_Camera);
			void renderChildren(const glm::mat4& a_mat4Transformation, const Viewport& a_Camera);

			void addComponent(IComponent* a_IComponent);

			GameObject(std::string a_strName, bool a_bIsRoot = true);
			GameObject(GameObject& a_GameObject, std::string a_strName, glm::vec3 a_v3Position, glm::vec3 a_v3Rotation, glm::vec3 a_v3Scale, bool a_bIsActiveSel = true);

			virtual ~GameObject();

			void resetDontDestroyParent(GameObject& a_NewParent);

		public:

			static GameObject* instantiate(GameObject& a_ParentGameObject, std::string a_strName, glm::vec3 a_v3Position, glm::vec3 a_v3Rotation, glm::vec3 a_v3Scale, bool a_bIsActiveSelf = true);
			static GameObject* instantiate(GameObject& a_ParentGameObject, std::string a_strName, bool a_bIsActiveSelf = true);

			glm::mat4 m_mat4Transformation{1.0f};
			Transform m_Transform;

			void addChild(GameObject* a_pChildGameObject);

			virtual void render(const glm::mat4& a_mat4Transformation, const ns_system::Viewport& a_Camera);
			virtual void update(float a_fDeltaTime);

			bool isComponentTypeExist(COMPONENT_TYPE a_ComponentType) const;

			void setAsParent(GameObject* a_pParentGameObject);

			bool getIsActiveSelf() const;
			bool getIsActiveInHierarchy() const;
			void setActive(bool a_bIsActive);

			inline std::string getName() const
			{
				return m_strName;
			}

			inline GameObject* setAsDontDestroy(bool a_bIsDontDestroy = true)
			{
				m_bIsDontDestroy = a_bIsDontDestroy;
				return this;
			}

			inline bool isDontDestroy() const
			{
				return m_bIsDontDestroy;
			}

			void logHierarchy(int l_iNumOfTabs);

			///Returns a component from the components vector, if the COMPONENT_TYPE is equal to the input.
			///If the component pointer is found it returns the component cast to the type specified else returns null.
			template<typename T_COMPONENT_TYPE, typename = typename std::enable_if<std::is_base_of<IComponent, T_COMPONENT_TYPE>::value>::type>
			T_COMPONENT_TYPE* getComponent(COMPONENT_TYPE a_COMPONENT_TYPE)
			{
				int l_iComponentCount = m_Components.size();
				for(int l_iComponentIndex = 0; l_iComponentIndex < l_iComponentCount; l_iComponentIndex++)
				{
					if (m_Components[l_iComponentIndex]->m_ComponentType == a_COMPONENT_TYPE)
					{
						return dynamic_cast<T_COMPONENT_TYPE*>(m_Components[l_iComponentIndex]);
					}
				}
				return nullptr;
			}
		};
	}
}