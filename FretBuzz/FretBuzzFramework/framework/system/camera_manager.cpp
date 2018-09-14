#pragma once
#include "camera_manager.h"
#include <iostream>

namespace ns_fretBuzz
{
	namespace ns_system
	{
		//singleton instance
		CameraManager* CameraManager::s_pInstance = nullptr;

		CameraManager::CameraManager()
		{
		
		}

		CameraManager::~CameraManager()
		{

		}

		CameraManager* CameraManager::initialize()
		{
			if (s_pInstance != nullptr)
			{
				std::cout << "CameraManager::initialize:: CameraManager already exists.\n";
				return nullptr;
			}

			s_pInstance = new CameraManager();
			return s_pInstance;
		}

		void CameraManager::destroy()
		{
			delete s_pInstance;
			s_pInstance = nullptr;
		}

		const CameraManager* CameraManager::get()
		{
			return s_pInstance;
		}
	}
}