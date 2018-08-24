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
			friend class IComponent;
		private:
			std::vector<IComponent*> m_Components;
			std::vector<GameObject*> m_Children;

			const std::string m_strName;
			const int m_iID;

			static int s_iID;

			void updateComponents(float a_fDeltaTime);
			void updateChildren(float a_fDeltaTime);

			void renderComponents(const glm::mat4& a_mat4Transformation, const Camera& a_Camera);
			void renderChildren(const glm::mat4& a_mat4Transformation, const Camera& a_Camera);

			bool m_bIsActive = true;
			void addComponent(IComponent* a_IComponent);

		public:
			GameObject(std::string a_strName);
			GameObject(std::string a_strName, glm::vec3 a_v3Position, glm::vec3 a_v3Rotation, glm::vec3 a_v3Scale);
			~GameObject();

			glm::mat4 m_mat4Transformation{1.0f};
			Transform m_Transform;

			void addChild(GameObject* a_pChildGameObject);

			virtual void render(const glm::mat4& a_mat4Transformation, const ns_system::Camera& a_Camera);
			virtual void update(float a_fDeltaTime);

			void setActive(bool a_bIsActive);

			bool isComponentTypeExist(COMPONENT_TYPE a_ComponentType) const;

			inline bool isActive() const
			{
				return m_bIsActive;
			}

			inline std::string getName() const
			{
				return m_strName;
			}

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