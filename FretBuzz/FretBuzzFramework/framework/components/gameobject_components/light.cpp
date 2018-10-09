#pragma once
#include "light.h"
#include "../../system/game_object.h"
#include "../../graphics/light_manager.h"
#include <iostream>

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		Light::Light(ns_system::GameObject& a_GameObj, LIGHT_TYPE a_LightType)
			: ns_system::IComponent(ns_system::COMPONENT_TYPE::LIGHT , a_GameObj ),
			m_LightType(a_LightType)
		{
			LightManager::s_registerLight(this);
		}

		Light::~Light()
		{
			LightManager::s_unregisterLight(this);
		}

		Light* Light::addToGameObject(ns_system::GameObject& a_GameObj, LIGHT_TYPE a_LightType)
		{
			return IComponent::isComponentOfTypeExistInGameObj(ns_system::COMPONENT_TYPE::LIGHT, &a_GameObj) ?
				nullptr : new Light(a_GameObj, a_LightType);
		}

		Light::LIGHT_TYPE Light::getType() const
		{
			return m_LightType;
		}

		void Light::setType(LIGHT_TYPE a_LIGHT_TYPE)
		{
			m_LightType = a_LIGHT_TYPE;
		}

		void Light::update(float a_fDeltaTime)
		{
			m_LightSource.m_v4LightPosition =  (m_LightType == LIGHT_TYPE::DIRECTIONAL) && (m_LightSource.m_v4LightPosition.w == 0.0f) ?
					glm::vec4(m_GameObject.m_Transform.getWorldPosition(), 0.0f):
					glm::vec4(m_GameObject.m_Transform.getWorldPosition(), 1.0f);

			m_LightSource.m_v3LightDirection = m_GameObject.m_Transform.getForward();
		}
	}
}