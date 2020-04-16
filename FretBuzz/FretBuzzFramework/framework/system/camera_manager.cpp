#include <fretbuzz_pch.h>
#include "camera_manager.h"
#include "graphics/post_process_manager.h"
#include <utils/Event/Delegate/delegate.h>

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		//singleton instance
		CameraManager* CameraManager::s_pInstance = nullptr;

		CameraManager::CameraManager()
			: ResourceContainer<std::vector<Camera*>>()
		{
			Delegate<Window::WINDOW_RESIZE_TYPE> l_Delegate;
			l_Delegate.Add<CameraManager, &CameraManager::windowResize>(this);
			Window::registerWindowResizeCallback(l_Delegate);
		}

		CameraManager::~CameraManager()
		{
			Delegate<Window::WINDOW_RESIZE_TYPE> l_Delegate;
			l_Delegate.Add<CameraManager, &CameraManager::windowResize>(this);
			Window::unregisterWindowResizeCallback(l_Delegate);
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
			return *(s_pInstance->m_Container[0]);
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

		void CameraManager::renderFrame(ns_system::SceneManager& a_SceneManager, const PostProcessManager& a_PostProcessManager)
		{
			int l_iCameraCount = m_Container.size();
			for (int l_iCameraIndex = 0; l_iCameraIndex < l_iCameraCount; l_iCameraIndex++)
			{
				if (m_Container[l_iCameraIndex]->isActiveAndEnabled())
				{
					Camera& l_CurrentCamera = *m_Container[l_iCameraIndex];
					//a_PostProcessManager.begin();
					Window::get()->setViewport(l_CurrentCamera.getViewport());
					a_SceneManager.renderActiveScenes(l_CurrentCamera);
					//a_PostProcessManager.draw(0, l_CurrentCamera);
				}
			}
		}

		void CameraManager::windowResize(int a_iWidth, int a_iHeight)
		{
			int l_iCameraCount = m_Container.size();
			for (int l_iCameraIndex = 0; l_iCameraIndex < l_iCameraCount; l_iCameraIndex++)
			{
				m_Container[l_iCameraIndex]->reset();
			}
		}

		std::vector<Camera*>& CameraManager::getCameras()
		{
			return m_Container;
		}
	}
}