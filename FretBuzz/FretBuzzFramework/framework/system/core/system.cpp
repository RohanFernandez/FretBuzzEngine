#include <fretbuzz_pch.h>
#include "system.h"
#include "asset_loader.h"
#include <imgui/imgui.h>

namespace ns_fretBuzz
{
	namespace ns_system
	{
		System* System::s_pInstance = nullptr;

		System::System(GameStartup& a_GameStartupData)
		{
			m_pEventManager = EventManager::Initialize();
			m_pLog = Log::initialize();
			m_pLayerManager = LayerManager::initialize(a_GameStartupData.m_vectLayers);
			m_pFontManager = ns_graphics::FontManager::initialize();
			m_pTimer = ns_system::TimerFPS::Initialize();

			m_pWindow = ns_graphics::Window::initialize(a_GameStartupData.m_uiScreenWidth, a_GameStartupData.m_uiScreenHeight, a_GameStartupData.m_strWindowName);
			m_pMasterRenderer = ns_graphics::MasterRenderer::initialize(*m_pWindow);
			m_pAudioEngine = AudioEngine::initialize();
			m_pResourceManager = ResourceManager::initialize();
			AssetLoader::loadAssets(m_pResourceManager);

			m_pInput = Input::initialize(*m_pWindow);
			m_pPhysicsEngine = PhysicsEngine::initialize({0.0f, 0.0f}, 8, 3);

			m_pSceneManager = SceneManager::initialize(a_GameStartupData.m_vectScenes);

#if _IS_DEBUG
			m_pInspector = ns_editor::Inspector::initialize();
			m_pMasterRenderer->setInspector(m_pInspector);
#endif
		}

		bool System::isInitialized(GameStartup& a_GameStartupData)
		{
			s_pInstance = new System(a_GameStartupData);
			return !(s_pInstance == nullptr ||
				s_pInstance->m_pAudioEngine == nullptr ||
				s_pInstance->m_pMasterRenderer == nullptr ||
				s_pInstance->m_pInput == nullptr ||
				s_pInstance->m_pPhysicsEngine == nullptr ||
				s_pInstance->m_pSceneManager == nullptr ||
				s_pInstance->m_pLayerManager == nullptr ||
				s_pInstance->m_pFontManager == nullptr ||
				s_pInstance->m_pLog == nullptr ||
				s_pInstance->m_pEventManager == nullptr ||
				s_pInstance->m_pTimer == nullptr	||
				s_pInstance->m_pWindow == nullptr
#if _IS_DEBUG
				|| s_pInstance->m_pInspector == nullptr
#endif
				);
		}

		System::~System()
		{
			m_pLayerManager->destroy();
			m_pSceneManager->destroy();
			m_pResourceManager->destroy();
			m_pAudioEngine->destroy();
			m_pInput->destroy();
			m_pMasterRenderer->destroy();
			m_pPhysicsEngine->destroy();
			m_pWindow->destroy();
			m_pFontManager->destroy();
			m_pLog->destroy();
			m_pTimer->destroy();

#if _IS_DEBUG
			 m_pInspector->destroy();
#endif

			s_pInstance = nullptr;
		}

		bool System::IsSystemPaused()
		{
			return s_pInstance->m_bIsSystemPaused;
		}

		void System::ToggleSystemPause(bool a_bIsPaused)
		{
			s_pInstance->m_bIsSystemPaused = a_bIsPaused;
			s_pInstance->m_pAudioEngine->ToggleMute(a_bIsPaused);
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

		void System::run(GameStartup& a_GameStartupData)
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
			TimerFPS& l_Timer = *(s_pInstance->m_pTimer);
			ns_graphics::Window& l_Window = *(s_pInstance->m_pWindow);
			float l_fTimeStep = 0.0f;

			while (!l_Window.isWindowClosed())
			{
				l_fTimeStep = s_pInstance->m_fDeltaTime * s_pInstance->m_fScaledTime * (s_pInstance->m_bIsSystemPaused ? 0.0f : 1.0f);

				if (!s_pInstance->m_bIsSystemPaused)
				{
					l_SceneManager.updateActiveScenes(l_fTimeStep);
					l_SceneManager.lateUpdateActiveScenes(l_fTimeStep);
					l_PhysicsEngine.step(l_fTimeStep);
					l_Input.Update();
				}
				
				l_Window.clear();
				l_MasterRenderer.render(l_SceneManager, s_pInstance->m_fDeltaTime);
				l_Window.update();
				
				l_Timer.update();
				s_pInstance->m_fDeltaTime = l_Timer.getDeltaTime();
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
				s_pInstance->m_pWindow->closeWindow();
			}
		}
	}
}