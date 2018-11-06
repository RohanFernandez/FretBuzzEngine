#pragma once
#include "system.h"
#include <iostream>
#include "asset_loader.h"


#include "../../scenes/init_state.h"
#include "../../scenes/mainmenu_state.h"
#include "../../scenes/score_state.h"
#include "../../scenes/threed_test_setup.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		System* System::s_pInstance = nullptr;

		const int System::START_SCREEN_WIDTH = 1200;;
		const int System::START_SCREEN_HEIGHT = 900;
		const std::string System::WINDOW_NAME = "FretBuzz";

		System::System()
		{
			m_pMasterRenderer = ns_graphics::MasterRenderer::initialize(START_SCREEN_WIDTH, START_SCREEN_HEIGHT, WINDOW_NAME, true);
			m_pAudioEngine = AudioEngine::initialize();
			m_pResourceManager = ResourceManager::initialize();
			AssetLoader::loadAssets(m_pResourceManager);

			m_pInput = Input::initialize(m_pMasterRenderer->getGLFWWindow());
			m_pPhysicsEngine = PhysicsEngine::initialize({0.0f, 0.0f}, 6, 2);


			m_vectScenes =
			{
				new SceneData<threed_test_scene>("3d_Test"),
				new SceneData<InitState>("initstate")
				/*new SceneData<MainMenuState>("mainmenustate"),
				new SceneData<ScoreState>("scorestate")*/

			};
			m_pSceneManager = SceneManager::initialize(m_vectScenes);

			//m_pGame = Game::intialize();
		}

		bool System::isInitialized()
		{
			s_pInstance = new System();
			return !(s_pInstance == nullptr ||
				    s_pInstance->m_pAudioEngine == nullptr ||
				    s_pInstance->m_pAudioEngine == nullptr ||
				    s_pInstance->m_pMasterRenderer == nullptr ||
				    s_pInstance->m_pInput == nullptr ||
					s_pInstance->m_pPhysicsEngine == nullptr || 
					s_pInstance->m_pSceneManager == nullptr );
		}

		System::~System()
		{
			m_pSceneManager->destroy();

			for (auto l_CurrentState = m_vectScenes.begin();
				l_CurrentState != m_vectScenes.end();)
			{
				delete *l_CurrentState;
				l_CurrentState = m_vectScenes.erase(l_CurrentState);
			}

			m_pResourceManager->destroy();

			m_pAudioEngine->destroy();
			m_pInput->destroy();
			m_pMasterRenderer->destroy();
			m_pPhysicsEngine->destroy();

			s_pInstance = nullptr;
		}

		void System::run()
		{
			if (s_pInstance != nullptr)
			{
				return;
			}

			if (!isInitialized())
			{
				destroy();
				return;
			}

			SceneManager& l_SceneManager = *(s_pInstance->m_pSceneManager);
			ns_graphics::MasterRenderer& l_MasterRenderer = *(s_pInstance->m_pMasterRenderer);
			Input& l_Input = *(s_pInstance->m_pInput);
			PhysicsEngine& l_PhysicsEngine = *(s_pInstance->m_pPhysicsEngine);

			float l_fCurrentDeltaTime = 0.0f;

			while (!l_MasterRenderer.isWindowClosed())
			{
				l_SceneManager.updateActiveScenes(l_fCurrentDeltaTime);
				l_PhysicsEngine.update(l_fCurrentDeltaTime);
				l_Input.Update();
				l_fCurrentDeltaTime = l_MasterRenderer.render(l_SceneManager);
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