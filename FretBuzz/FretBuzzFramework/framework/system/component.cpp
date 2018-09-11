#pragma once
#include "component.h"
#include "game_object.h"
#include <iostream>

namespace ns_fretBuzz
{
	namespace ns_system
	{
		IComponent::IComponent(COMPONENT_TYPE a_ComponentType, GameObject& a_GameObj, bool a_bIsEnabled)
			: m_ComponentType{ a_ComponentType },
	   		  m_GameObject{ a_GameObj },
			m_bIsEnabled{a_bIsEnabled}
		{
			m_GameObject.addComponent(this);

			if (m_bIsEnabled) { onEnable(); };
		};

		IComponent::~IComponent()
		{
			onDisable();
		}

		void IComponent::onEnable()
		{
			std::cout << "ON ENABLE:: "<< m_GameObject.getName()<<" \n";
		}

		void IComponent::onDisable()
		{
			std::cout << "ON DISABLE:: "<<m_GameObject.getName() <<"\n";
		}

		bool IComponent::isComponentOfTypeExistInGameObj(COMPONENT_TYPE a_ComponentType, const GameObject* a_pGameObject)
		{
			if (a_pGameObject->isComponentTypeExist(a_ComponentType))
			{
				std::cout << "IComponent::isComponentOfTypeExistInGameObj:: Component of type "<< a_ComponentType << " already exist in game object with name "<< a_pGameObject->m_strName <<"\n" ;
				return true;
			}
			return false;
		}

		void IComponent::onGameObjectActivated(bool a_bIsGameObjectActivated)
		{
			if (a_bIsGameObjectActivated && m_bIsEnabled)
			{
				onEnable();
			}
			else if (!a_bIsGameObjectActivated && m_bIsEnabled)
			{
				onDisable();
			}
		}

		void IComponent::setIsEnabled(bool a_bIsEnabled)
		{
			if (m_bIsEnabled != a_bIsEnabled)
			{
				m_bIsEnabled = a_bIsEnabled;

				if (m_bIsEnabled) 
				{
					onEnable();
				}
				else 
				{
					onDisable(); 
				}
			}
		}

		bool IComponent::isEnabled() const
		{
			return m_bIsEnabled;
		}

		bool IComponent::isActiveAndEnabled() const
		{
			return m_bIsEnabled && m_GameObject.getIsActiveInHierarchy();
		}
	}
}