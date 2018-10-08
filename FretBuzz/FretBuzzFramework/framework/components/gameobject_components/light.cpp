#pragma once
#include "light.h"
#include "../../system/game_object.h"
#include "../../graphics/light_manager.h"

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		Light::Light(ns_system::GameObject& a_GameObj, LIGHT_TYPE a_LightType)
			: ns_system::IComponent(ns_system::COMPONENT_TYPE::LIGHT , a_GameObj )
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

		void Light::updateUniforms(Shader& a_Shader)
		{
			a_Shader.setUniform4f(LightSource::UNIF_LIGHT_POSITION, m_LightSource.m_v4LightPosition);
			a_Shader.setUniform3f(LightSource::UNIF_LIGHT_DIRECTION, m_LightSource.m_v3LightDirection);
			a_Shader.setUniform3f(LightSource::UNIF_CONST_LIN_QUAD, m_LightSource.m_v3ConstLinQuad);

			a_Shader.setUniform3f(LightSource::UNIF_AMBIENT_COLOR, m_LightSource.m_v3AmbientColor);
			a_Shader.setUniform3f(LightSource::UNIF_DIFFUSE_COLOR, m_LightSource.m_v3Diffuse);
			a_Shader.setUniform3f(LightSource::UNIF_SPECULAR_COLOR, m_LightSource.m_v3Specular);

			if (m_LightType == LIGHT_TYPE::SPOT)
			{
				a_Shader.setUniform1f(LightSource::UNIF_INNER_CUT_OFF, m_LightSource.m_fInnerCutOff);
				a_Shader.setUniform1f(LightSource::UNIF_OUTER_CUT_OFF, m_LightSource.m_fOuterCutOff);
			}
		}

		void Light::update(float a_fDeltaTime)
		{
			m_LightSource.m_v4LightPosition = m_LightType == LIGHT_TYPE::DIRECTIONAL ? 
					glm::vec4(m_GameObject.m_Transform.getWorldPosition(), 0.0f):
					glm::vec4(m_GameObject.m_Transform.getWorldPosition(), 1.0f);

			m_LightSource.m_v3LightDirection = m_GameObject.m_Transform.getForward();
		}
	}
}