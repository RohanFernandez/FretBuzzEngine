#pragma once
#include "light.h"
#include "../system/game_object.h"
#include "../graphics/light_manager.h"

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		Light::Light(ns_system::GameObject& a_GameObj, LIGHT_TYPE a_LightType)
			: ns_system::IComponent(ns_system::COMPONENT_TYPE::LIGHT , a_GameObj )
		{
		
		}

		Light::~Light()
		{
			
		}

		Light* Light::addToGameObject(ns_system::GameObject& a_GameObj, LIGHT_TYPE a_LightType)
		{
			return IComponent::isComponentOfTypeExistInGameObj(ns_system::COMPONENT_TYPE::LIGHT, &a_GameObj) ?
				nullptr : new Light(a_GameObj, a_LightType);
		}
	}
}