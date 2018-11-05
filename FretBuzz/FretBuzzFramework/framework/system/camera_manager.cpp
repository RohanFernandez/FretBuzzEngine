#pragma once
#include "camera_manager.h"
#include <iostream>
#include "../graphics/post_process_manager.h"


namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		//singleton instance
		CameraManager* CameraManager::s_pInstance = nullptr;

		CameraManager::CameraManager()
			: ResourceContainer<std::vector<Camera*>>()
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

		Camera& CameraManager::getMainCamera()
		{
			return **m_Container.begin();
		}

		void CameraManager::registerCamera(Camera* a_pCamera)
		{
			if (a_pCamera == nullptr)
			{
				return;
			}

			registerResource(a_pCamera);
		}

		void CameraManager::s_registerCamera(Camera* a_pCamera)
		{
			s_pInstance->registerCamera(a_pCamera);
		}

		void CameraManager::unregisterCamera(Camera* a_pCamera)
		{
			unregisterResource(a_pCamera);
		}

		void CameraManager::s_unregisterCamera(Camera* a_pCamera)
		{
			s_pInstance->unregisterCamera(a_pCamera);
		}

		void CameraManager::updateViewMatrix()
		{
			int l_iCameraCount = m_Container.size();

			for (int l_iCameraIndex = 0; l_iCameraIndex < l_iCameraCount; l_iCameraIndex++)
			{
				if (m_Container[l_iCameraIndex]->isActiveAndEnabled())
				{
					m_Container[l_iCameraIndex]->updateViewMatrix();
				}
			}
		}

		void CameraManager::renderFrame(ns_system::Game& a_Game, const PostProcessManager& a_PostProcessManager)
		{
			int l_iCameraCount = m_Container.size();
			for (int l_iCameraIndex = 0; l_iCameraIndex < l_iCameraCount; l_iCameraIndex++)
			{
				if (m_Container[l_iCameraIndex]->isActiveAndEnabled())
				{
					Camera& l_CurrentCamera = *m_Container[l_iCameraIndex];
					a_PostProcessManager.begin();
					a_Game.renderFrame(l_CurrentCamera);
					a_PostProcessManager.draw(0, l_CurrentCamera);
				}
			}
		}

		void CameraManager::windowResize()
		{
			int l_iCameraCount = m_Container.size();
			for (int l_iCameraIndex = 0; l_iCameraIndex < l_iCameraCount; l_iCameraIndex++)
			{
				m_Container[l_iCameraIndex]->reset();
			}
		}
	}
}