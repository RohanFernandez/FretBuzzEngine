#pragma once
#include "system.h"
#include <iostream>
#include "asset_loader.h"


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
			m_pPhysicsEngine = PhysicsEngine::initialize({0.0f, 0.0f}, 6, 2);

			m_pSceneManager = SceneManager::initialize(a_GameStartupData.m_vectScenes);
		}

		bool System::isInitialized(GameStartupData& a_GameStartupData)
		{
			s_pInstance = new System(a_GameStartupData);
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
			m_pResourceManager->destroy();
			m_pAudioEngine->destroy();
			m_pInput->destroy();
			m_pMasterRenderer->destroy();
			m_pPhysicsEngine->destroy();

			s_pInstance = nullptr;
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