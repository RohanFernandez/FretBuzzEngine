#include <fretbuzz_pch.h>
#include "component.h"
#include "game_object.h"
#include <components/collider_2d.h>

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
			
			onAddedToGameObj();
			if (isActiveAndEnabled()) 
			{
				onEnable(); 
			};
		};

		IComponent::~IComponent()
		{
			onDisable();
			onRemovedFromGameObj();
		}

		void IComponent::onEnable()
		{
			std::cout << "ON ENABLE:: "<< m_GameObject.getName()<<" \n";
			callFuncInSiblings(&IComponent::onSiblingComponentEnabled);
		}

		void IComponent::onDisable()
		{
			std::cout << "ON DISABLE:: "<<m_GameObject.getName() <<"\n";
			callFuncInSiblings(&IComponent::onSiblingComponentDisabled);
		}

		bool IComponent::isComponentOfTypeExistInGameObj(COMPONENT_TYPE a_ComponentType, const GameObject* a_pGameObject)
		{
			if (a_pGameObject->isComponentTypeExist(a_ComponentType))
			{
				std::cout << "IComponent::isComponentOfTypeExistInGameObj:: Component of type "<< (int)a_ComponentType << " already exist in game object with name "<< a_pGameObject->m_strName <<"\n" ;
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

				if (m_bIsEnabled && m_GameObject.m_bIsActiveInHierarchy) 
				{
					onEnable();
				}
				else if(!m_bIsEnabled && m_GameObject.m_bIsActiveInHierarchy)
				{
					onDisable(); 
				}
			}
		}

		bool IComponent::getIsEnabled() const
		{
			return m_bIsEnabled;
		}

		bool IComponent::isActiveAndEnabled() const
		{
			return m_bIsEnabled && m_GameObject.getIsActiveInHierarchy();
		}

		void IComponent::onAddedToGameObj()
		{
			callFuncInSiblings(&IComponent::onSiblingComponentAdded);
		}

		void IComponent::onRemovedFromGameObj()
		{
			callFuncInSiblings(&IComponent::onSiblingComponentRemoved);
		}

		void IComponent::callFuncInSiblings(void(IComponent::* FUNC)(IComponent*))
		{
			const std::vector<IComponent*> l_vectComponents = m_GameObject.getAllComponents();

			for (auto l_CurrentComponent = l_vectComponents.begin();
				l_CurrentComponent != l_vectComponents.end(); l_CurrentComponent++)
			{
				IComponent* l_pCurrentComponent = *l_CurrentComponent;
				if (l_pCurrentComponent != this)
				{
					(l_pCurrentComponent->*FUNC)(this);
				}
			}
		}
	}
}