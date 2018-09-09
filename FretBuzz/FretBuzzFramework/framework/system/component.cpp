#pragma once
#include "component.h"
#include "game_object.h"
#include <iostream>

namespace ns_fretBuzz
{
	namespace ns_system
	{
		IComponent::IComponent(COMPONENT_TYPE a_ComponentType, GameObject& a_GameObj)
			: m_ComponentType{ a_ComponentType },
	   		  m_GameObject{ a_GameObj }
		{
			m_GameObject.addComponent(this);
		};

		void IComponent::update(float a_fDeltaTime)
		{

		}

		void IComponent::render(const glm::mat4& a_mat4Transformation, const Camera& a_Camera)
		{

		}

		void IComponent::debugRender(const glm::mat4& a_mat4Transformation, const Camera& a_Camera)
		{
			
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
	}
}