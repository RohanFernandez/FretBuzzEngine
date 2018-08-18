#pragma once
#include "game_object.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		//static counter that specifies the id.
		int GameObject::s_iID = 0;

		GameObject::GameObject(std::string a_strName)
			: m_iID{s_iID},
		     m_strName{a_strName},
			 m_Transform()
		{
			
		}

		GameObject::~GameObject()
		{
			for (std::vector<IComponent*>::iterator l_IComponentCurrent = m_Components.begin();
				l_IComponentCurrent != m_Components.end();)
			{
				delete *l_IComponentCurrent;
				l_IComponentCurrent = m_Components.erase(l_IComponentCurrent);
			}
		}

		void GameObject::addChild(GameObject* a_pIChildGameObject)
		{
			m_Children.emplace_back(a_pIChildGameObject);
		}

		void GameObject::update(float a_fDeltaTime)
		{
			if (!m_bIsActive)
			{
				return;
			}

			updateComponents(a_fDeltaTime);
			updateChildren(a_fDeltaTime);
		}

		void GameObject::updateComponents(float a_fDeltaTime)
		{
			m_Transform.updateModelMatrix();

			int l_iComponentCount = m_Components.size();
			for (int l_iComponentndex = 0; l_iComponentndex < l_iComponentCount; l_iComponentndex++)
			{
				m_Components[l_iComponentndex]->update(a_fDeltaTime);
			}
		}

		void GameObject::updateChildren(float a_fDeltaTime)
		{
			int l_iChildCount = m_Children.size();
			for (int l_iChildIndex = 0; l_iChildIndex < l_iChildCount; l_iChildIndex++)
			{
				m_Children[l_iChildIndex]->update(a_fDeltaTime);
			}
		}

		void GameObject::render(const Camera& a_Camera)
		{
			if (!m_bIsActive)
			{
				return;
			}

			renderComponents(a_Camera);
			renderChildren(a_Camera);
		}

		void GameObject::renderComponents(const Camera& a_Camera)
		{
			int l_iComponentCount = m_Components.size();
			for (int l_iComponentndex = 0; l_iComponentndex < l_iComponentCount; l_iComponentndex++)
			{
				m_Components[l_iComponentndex]->render(a_Camera);
			}
		}

		void GameObject::renderChildren(const Camera& a_Camera)
		{
			int l_iChildCount = m_Children.size();
			for (int l_iChildIndex = 0; l_iChildIndex < l_iChildCount; l_iChildIndex++)
			{
				m_Children[l_iChildIndex]->render(a_Camera);
			}
		}

		void GameObject::setActive(bool a_bIsActive)
		{
			m_bIsActive = a_bIsActive;
		}
	}
}