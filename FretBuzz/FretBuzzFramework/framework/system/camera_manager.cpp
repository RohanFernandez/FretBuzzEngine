#pragma once
#include "camera_manager.h"
#include <iostream>

namespace ns_fretBuzz
{
	namespace ns_graphics
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

		void CameraManager::registerCamera(Camera* a_pCamera)
		{
			if (a_pCamera == nullptr)
			{
				return;
			}

			m_vectCameras.emplace_back(a_pCamera);
		}

		void CameraManager::s_registerCamera(Camera* a_pCamera)
		{
			s_pInstance->registerCamera(a_pCamera);
		}

		void CameraManager::unregisterCamera(Camera* a_pCamera)
		{
			int l_iCameraCount = m_vectCameras.size();

			for (std::vector<Camera*>::iterator l_Iterator = m_vectCameras.begin(),
				l_iIteratorEnd = m_vectCameras.end();
				l_Iterator != l_iIteratorEnd;
				l_Iterator++)
			{
				if (*l_Iterator == a_pCamera)
				{
					m_vectCameras.erase(l_Iterator);
					return;
				}
				std::cout << "CameraManager::unregisterCamera:: Failed to find Camera to unregister in Camera list\n";
			}
		}

		void CameraManager::s_unregisterCamera(Camera* a_pCamera)
		{
			s_pInstance->unregisterCamera(a_pCamera);
		}

		void CameraManager::updateViewMatrix()
		{
			int l_iCameraCount = m_vectCameras.size();

			for (int l_iCameraIndex = 0; l_iCameraIndex < l_iCameraCount; l_iCameraIndex++)
			{
				if (m_vectCameras[l_iCameraIndex]->isActiveAndEnabled())
				{
					m_vectCameras[l_iCameraIndex]->updateViewMatrix();
				}
			}
		}

		void CameraManager::renderFrame(ns_system::Game& a_Game)
		{
			int l_iCameraCount = m_vectCameras.size();
			for (int l_iCameraIndex = 0; l_iCameraIndex < l_iCameraCount; l_iCameraIndex++)
			{
				if (m_vectCameras[l_iCameraIndex]->isActiveAndEnabled())
				{
					a_Game.renderFrame(*m_vectCameras[l_iCameraIndex]);
				}
			}
		}

		void CameraManager::windowResize()
		{
			int l_iCameraCount = m_vectCameras.size();
			for (int l_iCameraIndex = 0; l_iCameraIndex < l_iCameraCount; l_iCameraIndex++)
			{
				m_vectCameras[l_iCameraIndex]->reset();
			}
		}
	}
}