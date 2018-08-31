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
			m_pAudioEngine = new AudioEngine();
			m_pMasterRenderer = new MasterRenderer(START_SCREEN_WIDTH, START_SCREEN_HEIGHT, WINDOW_NAME, true);
			m_pInput = new Input(m_pMasterRenderer->getGLFWWindow());

			m_pResourceManager = new ResourceManager();
			AssetLoader::loadAssets(m_pResourceManager);

			m_pPhysicsEngine = new PhysicsEngine({0.0f, -9.8f});

			m_pGame = new Game();
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
			if (m_pResourceManager != nullptr)
			{
				delete m_pResourceManager;
				m_pResourceManager = nullptr;
			}

			if (m_pGame != nullptr)
			{
				delete m_pGame;
				m_pGame = nullptr;
			}

			if (m_pAudioEngine != nullptr)
			{
				delete m_pAudioEngine;
				m_pAudioEngine = nullptr;
			}

			if (m_pInput != nullptr)
			{
				delete m_pInput;
				m_pInput = nullptr;
			}

			if (m_pMasterRenderer != nullptr)
			{
				delete m_pMasterRenderer;
				m_pMasterRenderer = nullptr;
			}

			if (m_pPhysicsEngine != nullptr)
			{
				delete m_pPhysicsEngine;
				m_pPhysicsEngine = nullptr;
			}

			if (s_pInstance == this)
			{
				s_pInstance = nullptr;
			}
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
			MasterRenderer& l_MasterRenderer = *(s_pInstance->m_pMasterRenderer);
			Input& l_Input = *(s_pInstance->m_pInput);

			float l_fCurrentDeltaTime = 0.0f;

			while (!l_MasterRenderer.isWindowClosed())
			{
				l_Game.updateScenes(l_fCurrentDeltaTime);

				l_Input.Update(l_fCurrentDeltaTime);
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