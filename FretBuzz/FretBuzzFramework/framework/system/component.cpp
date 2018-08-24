#pragma once
#include "component.h"
#include "game_object.h"

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
	}
}