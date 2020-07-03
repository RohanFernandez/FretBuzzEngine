#include <fretbuzz_pch.h>
#include "system.h"
#include "asset_loader.h"
#include <imgui/imgui.h>
#include <system_layer/editor_system_layer.h>
#include <system_layer/game_system_layer.h>

namespace ns_fretBuzz
{
	System* System::s_pInstance = nullptr;

	System::System(GameStartup& a_GameStartupData)
	{
		m_pEventManager = EventManager::Initialize();
		m_pLog = Log::initialize();
		m_pLayerManager = LayerManager::initialize(a_GameStartupData.m_vectLayers);
		m_pSystemLayerStack = SystemLayerStack::Initialize(2);
		m_pFontManager = FontManager::initialize();

		m_pWindow = Window::initialize(a_GameStartupData.m_uiScreenWidth, a_GameStartupData.m_uiScreenHeight, a_GameStartupData.m_strWindowName);
		m_pMasterRenderer = MasterRenderer::initialize(*m_pWindow);
		m_pAudioEngine = AudioEngine::initialize();
		m_pResourceManager = ResourceManager::initialize();
		AssetLoader::loadAssets(m_pResourceManager);

		m_pInput = Input::initialize(*m_pWindow);
		m_pPhysicsEngine = PhysicsEngine::initialize({0.0f, 0.0f}, 8, 3);

		m_pSceneManager = SceneManager::initialize(a_GameStartupData.m_vectScenes);

		m_pSystemLayerStack->AddLayer<GameSystemLayer>("Game");
		m_pSystemLayerStack->AddLayer<EditorSystemLayer>("Editor");
#if _DEBUG
		/*m_pInspector = ns_editor::Inspector::initialize();
		m_pMasterRenderer->setInspector(m_pInspector);*/
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
			s_pInstance->m_pSystemLayerStack == nullptr ||
			s_pInstance->m_pEventManager == nullptr ||
			s_pInstance->m_pWindow == nullptr
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
		m_pSystemLayerStack->destroy();
		m_pFontManager->destroy();
		m_pLog->destroy();

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

	const float& System::GetScaledTime()
	{
		return s_pInstance->m_fScaledTime;
	}

	const float& System::GetDeltaTime()
	{
		return s_pInstance->m_fDeltaTime;
	}

	const float& System::GetUnscaledTime()
	{
		return s_pInstance->m_fUnscaledTime;
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
		MasterRenderer& l_MasterRenderer = *(s_pInstance->m_pMasterRenderer);
		Input& l_Input = *(s_pInstance->m_pInput);
		PhysicsEngine& l_PhysicsEngine = *(s_pInstance->m_pPhysicsEngine);
		Window& l_Window = *(s_pInstance->m_pWindow);
		SystemLayerStack& l_SystemLayerStack = *(s_pInstance->m_pSystemLayerStack);

		float l_fLastFrameTime = (float)glfwGetTime();

		while (!l_Window.isWindowClosed())
		{	

			s_pInstance->m_fUnscaledTime = (float)glfwGetTime() - l_fLastFrameTime;
			l_fLastFrameTime = (float)glfwGetTime();
			s_pInstance->m_fDeltaTime = s_pInstance->m_fUnscaledTime * s_pInstance->m_fScaledTime * (s_pInstance->m_bIsSystemPaused ? 0.0f : 1.0f);
			l_Window.clear();

			///update all layers
			for (auto l_Layer = l_SystemLayerStack.begin(); l_Layer != l_SystemLayerStack.end(); l_Layer++)
			{
				(*l_Layer)->update(s_pInstance->m_fDeltaTime, l_SceneManager);
			}

			///late update all layers
			for (auto l_Layer = l_SystemLayerStack.begin(); l_Layer != l_SystemLayerStack.end(); l_Layer++)
			{
				(*l_Layer)->lateUpdate(s_pInstance->m_fDeltaTime, l_SceneManager);
			}

			l_MasterRenderer.render(l_SceneManager, s_pInstance->m_fDeltaTime);

			///add render commands 
			for (auto l_Layer = l_SystemLayerStack.begin(); l_Layer != l_SystemLayerStack.end(); l_Layer++)
			{
				(*l_Layer)->render(l_SceneManager);
			}

			l_PhysicsEngine.step(s_pInstance->m_fDeltaTime);
			l_Input.Update();
			l_Window.update();
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
			s_pInstance->m_pMasterRenderer->close();
			s_pInstance->m_pWindow->closeWindow();
		}
	}
}