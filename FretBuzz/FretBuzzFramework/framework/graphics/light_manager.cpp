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

		void LightManager::setAllLightUniforms(Shader& a_shader)
		{
			int l_iLightCount = m_vectResourceContainer.size();
			for (int l_iLightindex = 0; l_iLightindex < l_iLightCount; l_iLightindex++)
			{
				if (m_vectResourceContainer[l_iLightindex]->getIsEnabled())
				{
					m_vectResourceContainer[l_iLightindex]->updateUniforms(a_shader, l_iLightindex);
				}
			}
		}

		void LightManager::s_setAllLightUniforms(Shader& a_shader)
		{
			s_pInstance->setAllLightUniforms(a_shader);
		}
	}
}