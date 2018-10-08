#pragma once
#include "system.h"
#include <iostream>
#include "asset_loader.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		System* System::s_pInstance = nullptr;

		const int System::START_SCREEN_WIDTH = 800;;
		const int System::START_SCREEN_HEIGHT = 600;
		const std::string System::WINDOW_NAME = "FretBuzz";

		System::System()
		{
			m_pMasterRenderer = ns_graphics::MasterRenderer::initialize(START_SCREEN_WIDTH, START_SCREEN_HEIGHT, WINDOW_NAME, true);
			m_pAudioEngine = AudioEngine::initialize();
			m_pResourceManager = ResourceManager::initialize();
			AssetLoader::loadAssets(m_pResourceManager);

			m_pInput = Input::initialize(m_pMasterRenderer->getGLFWWindow());
			m_pPhysicsEngine = PhysicsEngine::initialize({0.0f, 0.0f}, 6, 2);

			m_pGame = Game::intialize();
		}

		bool System::isInitialized()
		{
			s_pInstance = new System();
			return !(s_pInstance == nullptr ||
				    s_pInstance->m_pAudioEngine == nullptr ||
				    s_pInstance->m_pAudioEngine == nullptr ||
				    s_pInstance->m_pMasterRenderer == nullptr ||
				    s_pInstance->m_pInput == nullptr ||
					s_pInstance->m_pPhysicsEngine == nullptr);
		}

		System::~System()
		{
			m_pResourceManager->destroy();

			m_pGame->destroy();
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

			Game& l_Game = *(s_pInstance->m_pGame);
			ns_graphics::MasterRenderer& l_MasterRenderer = *(s_pInstance->m_pMasterRenderer);
			Input& l_Input = *(s_pInstance->m_pInput);
			PhysicsEngine& l_PhysicsEngine = *(s_pInstance->m_pPhysicsEngine);

			float l_fCurrentDeltaTime = 0.0f;

			while (!l_MasterRenderer.isWindowClosed())
			{
				l_Game.updateScenes(l_fCurrentDeltaTime);
				l_PhysicsEngine.update(l_fCurrentDeltaTime);
				l_Input.Update();
				l_fCurrentDeltaTime = l_MasterRenderer.render(l_Game);
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