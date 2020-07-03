#include <fretbuzz_pch.h>
#include <fretbuzz.h>
#include "camera_manager.h"
#include "graphics/post_process_manager.h"

namespace ns_fretBuzz
{
	//singleton instance
	CameraManager* CameraManager::s_pInstance = nullptr;

	CameraManager::CameraManager()
		: ResourceContainer<std::vector<Camera*>>()
	{
		Delegate<Window::WINDOW_RESIZE_TYPE> l_Delegate;
		l_Delegate.Add<CameraManager, &CameraManager::windowResize>(this);
			EventManager::Subscribe<Window::WINDOW_RESIZE_TYPE>(FRETBUZZ_ON_WINDOW_RESIZE, l_Delegate);
	}

	CameraManager::~CameraManager()
	{
		Delegate<Window::WINDOW_RESIZE_TYPE> l_Delegate;
		l_Delegate.Add<CameraManager, &CameraManager::windowResize>(this);
		EventManager::Unsubscribe<Window::WINDOW_RESIZE_TYPE>(FRETBUZZ_ON_WINDOW_RESIZE, l_Delegate);
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
		size_t l_iCameraCount = m_Container.size();

		for (size_t l_iCameraIndex = 0; l_iCameraIndex < l_iCameraCount; l_iCameraIndex++)
		{
			if (m_Container[l_iCameraIndex]->isActiveAndEnabled())
			{
				m_Container[l_iCameraIndex]->updateViewMatrix();
			}
		}
	}

	void CameraManager::renderFrame(SceneManager& a_SceneManager, const PostProcessManager& a_PostProcessManager)
	{
		size_t l_iCameraCount = m_Container.size();
		for (size_t l_iCameraIndex = 0; l_iCameraIndex < l_iCameraCount; l_iCameraIndex++)
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
		size_t l_iCameraCount = m_Container.size();
		for (size_t l_iCameraIndex = 0; l_iCameraIndex < l_iCameraCount; l_iCameraIndex++)
		{
			m_Container[l_iCameraIndex]->reset();
		}
	}

	std::vector<Camera*>& CameraManager::getCameras()
	{
		return m_Container;
	}
}