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
			m_Components.emplace_back(&m_Transform);
		}

		GameObject::~GameObject()
		{
			for (std::vector<IComponent*>::iterator l_IComponentCurrent = m_Components.begin() + 1;
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

		void GameObject::render()
		{
			if (!m_bIsActive)
			{
				return;
			}

			renderComponents();
			renderChildren();
		}

		void GameObject::renderComponents()
		{
			int l_iComponentCount = m_Components.size();
			for (int l_iComponentndex = 0; l_iComponentndex < l_iComponentCount; l_iComponentndex++)
			{
				m_Components[l_iComponentndex]->render();
			}
		}

		void GameObject::renderChildren()
		{
			int l_iChildCount = m_Children.size();
			for (int l_iChildIndex = 0; l_iChildIndex < l_iChildCount; l_iChildIndex++)
			{
				m_Children[l_iChildIndex]->render();
			}
		}

		void GameObject::setActive(bool a_bIsActive)
		{
			m_bIsActive = a_bIsActive;
		}
	}
}