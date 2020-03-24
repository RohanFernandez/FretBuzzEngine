#include <fretbuzz_pch.h>
#include "system.h"
#include "asset_loader.h"
#include <imgui/imgui.h>

namespace ns_fretBuzz
{
	namespace ns_system
	{
		System* System::s_pInstance = nullptr;

		System::System(GameStartupData& a_GameStartupData)
		{
			m_pMasterRenderer = ns_graphics::MasterRenderer::initialize(a_GameStartupData.m_uiScreenWidth, a_GameStartupData.m_uiScreenHeight, a_GameStartupData.m_strWindowName, true);
			m_pAudioEngine = AudioEngine::initialize();
			m_pResourceManager = ResourceManager::initialize();
			AssetLoader::loadAssets(m_pResourceManager);

			m_pInput = Input::initialize(m_pMasterRenderer->getGLFWWindow());
			m_pPhysicsEngine = PhysicsEngine::initialize({0.0f, 0.0f}, 8, 3);

			m_pSceneManager = SceneManager::initialize(a_GameStartupData.m_vectScenes);
		}

		bool System::isInitialized(GameStartupData& a_GameStartupData)
		{
			s_pInstance = new System(a_GameStartupData);
			return !(s_pInstance == nullptr ||
				    s_pInstance->m_pAudioEngine == nullptr ||
				    s_pInstance->m_pMasterRenderer == nullptr ||
				    s_pInstance->m_pInput == nullptr ||
					s_pInstance->m_pPhysicsEngine == nullptr || 
					s_pInstance->m_pSceneManager == nullptr );
		}

		System::~System()
		{
			m_pSceneManager->destroy();
			m_pResourceManager->destroy();
			m_pAudioEngine->destroy();
			m_pInput->destroy();
			m_pMasterRenderer->destroy();
			m_pPhysicsEngine->destroy();

			s_pInstance = nullptr;
		}

		bool System::IsSystemPaused()
		{
			return s_pInstance->m_bIsSystemPaused;
		}

		void System::ToggleSystemPause(bool a_bIsPause)
		{
			s_pInstance->m_bIsSystemPaused = a_bIsPause;
		}

		void System::SetScaledTime(float a_fScaledTime)
		{
			s_pInstance->m_fScaledTime = a_fScaledTime;
		}

		float System::GetScaledTime()
		{
			return s_pInstance->m_fScaledTime;
		}

		float System::GetDeltaTime()
		{
			return s_pInstance->m_fDeltaTime;
		}

		void System::run(GameStartupData& a_GameStartupData)
		{
			if (s_pInstance != nullptr)
			{
				return;
			}

			if (!isInitialized(a_GameStartupData))
			{
				destroy();
				return;
			}

			SceneManager& l_SceneManager = *(s_pInstance->m_pSceneManager);
			ns_graphics::MasterRenderer& l_MasterRenderer = *(s_pInstance->m_pMasterRenderer);
			Input& l_Input = *(s_pInstance->m_pInput);
			PhysicsEngine& l_PhysicsEngine = *(s_pInstance->m_pPhysicsEngine);
			float l_fTimeStep = 0.0f;

			while (!l_MasterRenderer.isWindowClosed())
			{
				l_fTimeStep = s_pInstance->m_fDeltaTime * s_pInstance->m_fScaledTime * (s_pInstance->m_bIsSystemPaused ? 0.0f : 1.0f);

				if (!s_pInstance->m_bIsSystemPaused)
				{
					l_SceneManager.updateActiveScenes(l_fTimeStep);
					l_PhysicsEngine.step(l_fTimeStep);
					l_Input.Update();
				}
				s_pInstance->m_fDeltaTime = l_MasterRenderer.render(l_SceneManager);
			}

			destroy();
		}

		void System::destroy()
		{
			if (s_pInstance != nullptr)
			{
				delete s_pInstance;
				s_pInstance = nullptr;
			}
		}

		void System::close()
		{
			if (s_pInstance != nullptr)
			{
				s_pInstance->m_pMasterRenderer->closeWindow();
			}
		}
	}
}