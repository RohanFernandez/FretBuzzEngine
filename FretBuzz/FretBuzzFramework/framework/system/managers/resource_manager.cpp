#pragma once
#include "resource_manager.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		///singletor instance
		ResourceManager* ResourceManager::s_pInstance = nullptr;

		ResourceManager::ResourceManager()
		{
			if (s_pInstance != nullptr)
			{
				return;
			}
			s_pInstance = this;
		}

		ResourceManager::~ResourceManager()
		{
			if (s_pInstance == this)
			{
				T_MAP_RESOURCE& l_mapResource = s_pInstance->m_mapResource;
				for (auto l_currentResource = l_mapResource.begin(),
					l_endResource = l_mapResource.end();
					l_currentResource != l_endResource;
					l_currentResource++)
				{
					IResource*& l_pCurrentResourceInterface = l_currentResource->second;
					l_pCurrentResourceInterface->unloadResources();

					delete l_pCurrentResourceInterface;
					l_pCurrentResourceInterface = nullptr;
				}

				s_pInstance = nullptr;
			}
		}
	}
}