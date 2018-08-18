#pragma once

#include "../components/transform.h"
#include <vector>
#include <string>

namespace ns_fretBuzz
{
	namespace ns_system
	{
		class Transform;
		class GameObject
		{
		private:
			std::vector<IComponent*> m_Components;
			std::vector<GameObject*> m_Children;

			const std::string m_strName;
			const int m_iID;

			static int s_iID;

			void updateComponents(float a_fDeltaTime);
			void updateChildren(float a_fDeltaTime);

			void renderComponents();
			void renderChildren();

			bool m_bIsActive = true;

		public:
			GameObject(std::string a_strName);
			~GameObject();

			Transform m_Transform;

			template<typename T, typename = typename std::enable_if<std::is_base_of<IComponent, T>::value>::type>
			T& addComponent(T a_IComponent)
			{
				T* l_ComponentAdded = new T(a_IComponent);
				m_Components.emplace_back(l_ComponentAdded);
				return *l_ComponentAdded;
			}

			void addChild(GameObject* a_pIComponent);

			virtual void render();
			virtual void update(float a_fDeltaTime);

			void setActive(bool a_bIsActive);

			inline bool isActive() const
			{
				return m_bIsActive;
			}

			inline std::string getName() const
			{
				return m_strName;
			}
		};
	}
}