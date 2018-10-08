#pragma once
#include "../components/light.h"
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
	}
}