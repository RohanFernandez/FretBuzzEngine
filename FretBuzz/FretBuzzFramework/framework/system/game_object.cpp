#pragma once
#include "game_object.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		//static counter that specifies the id.
		int GameObject::s_iID = 0;

		GameObject::GameObject(std::string a_strName)
			: m_iID{++s_iID},
		     m_strName{a_strName},
			 m_Transform()
		{
			
		}

		GameObject::GameObject(std::string a_strName, glm::vec3 a_v3Position, glm::vec3 a_v3Rotation, glm::vec3 a_v3Scale)
			: m_iID{ ++s_iID },
			m_strName{ a_strName },
			m_Transform(a_v3Position, a_v3Rotation, a_v3Scale)
		{

		}

		GameObject::~GameObject()
		{
			for (std::vector<IComponent*>::iterator l_IComponentCurrent = m_Components.begin();
				l_IComponentCurrent != m_Components.end();)
			{
				delete (*l_IComponentCurrent);
				l_IComponentCurrent = m_Components.erase(l_IComponentCurrent);
			}
		}

		void GameObject::addChild(GameObject* a_pIChildGameObject)
		{
			m_Children.emplace_back(a_pIChildGameObject);
		}

		void GameObject::addComponent(IComponent* a_IComponent)
		{
			m_Components.emplace_back(a_IComponent);
		}

		void GameObject::update(float a_fDeltaTime)
		{
			updateComponents(a_fDeltaTime);
			updateChildren(a_fDeltaTime);
		}

		void GameObject::updateComponents(float a_fDeltaTime)
		{
			int l_iComponentCount = m_Components.size();
			for (int l_iComponentndex = 0; l_iComponentndex < l_iComponentCount; l_iComponentndex++)
			{
				m_Components[l_iComponentndex]->update(a_fDeltaTime);
			}
		}

		void GameObject::updateChildren(float a_fDeltaTime)
		{
			int l_iChildCount = m_Children.size();
			GameObject* l_pCurrentGameObject = nullptr;

			for (int l_iChildIndex = 0; l_iChildIndex < l_iChildCount; l_iChildIndex++)
			{
				l_pCurrentGameObject = m_Children[l_iChildIndex];
				if (l_pCurrentGameObject->m_bIsActive)
				{
					l_pCurrentGameObject->update(a_fDeltaTime);
				}
			}
		}

		void GameObject::render(const glm::mat4& a_mat4Transformation, const Camera& a_Camera)
		{
			m_mat4Transformation = a_mat4Transformation * m_Transform.getModelMatrix();

			renderComponents(m_mat4Transformation, a_Camera);
			renderChildren(m_mat4Transformation, a_Camera);
		}

		void GameObject::renderComponents(const glm::mat4& a_mat4Transformation, const Camera& a_Camera)
		{
			int l_iComponentCount = m_Components.size();
			for (int l_iComponentndex = 0; l_iComponentndex < l_iComponentCount; l_iComponentndex++)
			{
				m_Components[l_iComponentndex]->render(a_mat4Transformation, a_Camera);
			}
		}

		void GameObject::renderChildren(const glm::mat4& a_mat4Transformation, const Camera& a_Camera)
		{
			GameObject* l_pCurrentGameObject = nullptr;

			int l_iChildCount = m_Children.size();
			for (int l_iChildIndex = 0; l_iChildIndex < l_iChildCount; l_iChildIndex++)
			{
				l_pCurrentGameObject = m_Children[l_iChildIndex];

				if (l_pCurrentGameObject->isActive())
				{
					l_pCurrentGameObject->render(a_mat4Transformation, a_Camera);
				}
			}
		}

		void GameObject::setActive(bool a_bIsActive)
		{
			m_bIsActive = a_bIsActive;
		}

		bool GameObject::isComponentTypeExist(COMPONENT_TYPE a_ComponentType) const
		{
			int l_iComponentCount = m_Components.size();
			for (int l_iComponentIndex = 0; l_iComponentIndex < l_iComponentCount; l_iComponentIndex++)
			{
				if (m_Components[l_iComponentIndex]->m_ComponentType == a_ComponentType)
				{
					return true;
				}
			}
			return false;
		}
	}
}