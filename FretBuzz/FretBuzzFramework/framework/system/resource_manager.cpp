#include <fretbuzz_pch.h>
#include "resource_manager.h"

namespace ns_fretBuzz
{
	///singletor instance
	ResourceManager* ResourceManager::s_pInstance = nullptr;

	ResourceManager::ResourceManager()
	{
			
	}

	ResourceManager::~ResourceManager()
	{
		T_MAP_RESOURCE& l_mapResource = s_pInstance->m_mapResource;
		for (auto l_currentResource = l_mapResource.begin(),
			l_endResource = l_mapResource.end();
			l_currentResource != l_endResource;
			l_currentResource++)
		{
			IResource*& l_pCurrentResourceInterface = l_currentResource->second;

			delete l_pCurrentResourceInterface;
			l_pCurrentResourceInterface = nullptr;

		}
		l_mapResource.clear();
	}

	ResourceManager* ResourceManager::initialize()
	{
		if (s_pInstance != nullptr)
		{
			std::cout << "ResourceManager::initialize:: ResourceManager already exists.\n";
			return nullptr;
		}
		s_pInstance = new ResourceManager();
		return s_pInstance;
	}

	void ResourceManager::destroy()
	{
		delete s_pInstance;
		s_pInstance = nullptr;
	}

	const ResourceManager* ResourceManager::get()
	{
		return s_pInstance;
	}


	void ResourceManager::destroyResource(IManagedResource* a_pManagedResource)
	{
		a_pManagedResource->destroyResource();
	}
}