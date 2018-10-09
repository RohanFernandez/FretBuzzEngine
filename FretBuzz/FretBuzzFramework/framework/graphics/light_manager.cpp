#pragma once
#include "../components/gameobject_components/light.h"
#include "light_manager.h"
#include <iostream>

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		//singleton instance
		LightManager* LightManager::s_pInstance = nullptr;

		LightManager::LightManager()
			:ResourceContainer<Light>()
		{
			
		}

		LightManager::~LightManager()
		{
		
		}

		LightManager* LightManager::initialize()
		{
			if (s_pInstance != nullptr)
			{
				std::cout << "LightManager::initialize:: LightManager already exists.\n";
				return nullptr;
			}

			s_pInstance = new LightManager();
			return s_pInstance;
		}

		void LightManager::destroy()
		{
			delete s_pInstance;
			s_pInstance = nullptr;
		}

		const LightManager* LightManager::get()
		{
			return s_pInstance;
		}

		void LightManager::registerLight(Light* a_pLight)
		{
			registerResource(*a_pLight);
		}

		void LightManager::s_registerLight(Light* a_pLight)
		{
			s_pInstance->registerLight(a_pLight);
		}

		void LightManager::unregisterLight(Light* a_pLight)
		{
			unregisterResource(*a_pLight);
		}

		void LightManager::s_unregisterLight(Light* a_pLight)
		{
			s_pInstance->unregisterLight(a_pLight);
		}

		void LightManager::setAllLightUniforms(Shader& a_Shader)
		{
			int l_iDirectionalLightIndex = 0;
			int l_iPointLightIndex = 0;
			int l_iSpotLightIndex = 0;

			int l_iLightCount = m_vectResourceContainer.size();
			for (int l_iLightindex = 0; l_iLightindex < l_iLightCount; l_iLightindex++)
			{
				Light& l_Light = *m_vectResourceContainer[l_iLightindex];
				std::string l_strLightIndex;

				if (l_Light.getIsEnabled())
				{
					Light::LIGHT_TYPE l_LightType = l_Light.getType();

					if (l_LightType == Light::LIGHT_TYPE::DIRECTIONAL)
					{
						l_strLightIndex = Light::LightSource::UNIF_DIRECTIONAL_LIGHT + std::to_string(l_iDirectionalLightIndex);
						l_iDirectionalLightIndex++;
					}
					else if (l_LightType == Light::LIGHT_TYPE::POINT)
					{
						l_strLightIndex = Light::LightSource::UNIF_POINT_LIGHT + std::to_string(l_iPointLightIndex);
						l_iPointLightIndex++;
					}
					else if (l_LightType == Light::LIGHT_TYPE::SPOT)
					{
						l_strLightIndex = Light::LightSource::UNIF_SPOT_LIGHT + std::to_string(l_iSpotLightIndex);
						l_iSpotLightIndex++;
						a_Shader.setUniform1f((l_strLightIndex + Light::LightSource::UNIF_INNER_CUT_OFF).c_str(), l_Light.m_LightSource.m_fInnerCutOff);
						a_Shader.setUniform1f((l_strLightIndex + Light::LightSource::UNIF_OUTER_CUT_OFF).c_str(), l_Light.m_LightSource.m_fOuterCutOff);
					}
				
					a_Shader.setUniform4f((l_strLightIndex + Light::LightSource::UNIF_LIGHT_POSITION).c_str(), l_Light.m_LightSource.m_v4LightPosition);
					a_Shader.setUniform3f((l_strLightIndex + Light::LightSource::UNIF_LIGHT_DIRECTION).c_str(), l_Light.m_LightSource.m_v3LightDirection);
					a_Shader.setUniform3f((l_strLightIndex + Light::LightSource::UNIF_CONST_LIN_QUAD).c_str(), l_Light.m_LightSource.m_v3ConstLinQuad);

					a_Shader.setUniform3f((l_strLightIndex + Light::LightSource::UNIF_AMBIENT_COLOR).c_str(), l_Light.m_LightSource.m_v3AmbientColor);
					a_Shader.setUniform3f((l_strLightIndex + Light::LightSource::UNIF_DIFFUSE_COLOR).c_str(), l_Light.m_LightSource.m_v3Diffuse);
					a_Shader.setUniform3f((l_strLightIndex + Light::LightSource::UNIF_SPECULAR_COLOR).c_str(), l_Light.m_LightSource.m_v3Specular);
					a_Shader.setUniform1f((l_strLightIndex + Light::LightSource::UNIF_INTENSITY).c_str(), l_Light.m_LightSource.m_fIntensity);
				}
			}
		}

		void LightManager::s_setAllLightUniforms(Shader& a_shader)
		{
			s_pInstance->setAllLightUniforms(a_shader);
		}
	}
}