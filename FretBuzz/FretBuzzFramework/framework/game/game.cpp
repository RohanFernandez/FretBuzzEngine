#pragma once
#include "game.h"
#include "../system/input.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		Game::Game()
			: IUpdateTimer()
		{
			////Testing Start//////
			ns_graphics::Shader testShader("resources//shaders//vertShader.txt", "resources//shaders//fragShader.txt");
			ns_graphics::Texture testTexture("resources//textures//darksiders.jpg");

			ResourceManager::addResource<ns_graphics::Shader>("tShader", testShader);
			ResourceManager::addResource<ns_graphics::Texture>("darksider", testTexture);

			////Testing End//////

			m_vectScenes =
			{
				new SceneData<InitState>("initstate"),
				new SceneData<MainMenuState>("mainmenustate"),
				new SceneData<ScoreState>("scorestate")
			};
			m_pSceneManager = new SceneManager(m_vectScenes);
		}

		Game::~Game()
		{
			if (m_pSceneManager != nullptr)
			{
				delete m_pSceneManager;
				m_pSceneManager = nullptr;
			}

			for (auto l_CurrentState = m_vectScenes.cbegin(), l_EndStateIndex = m_vectScenes.cend();
				l_CurrentState != l_EndStateIndex; l_CurrentState++)
			{
				delete *l_CurrentState;
			}
		}

		void Game::onUpdate(const float a_fDeltaTime)
		{
			if (Input::IsKeyDown(GLFW_KEY_I))
			{
				SceneManager::s_loadScene("initstate");
			}
			else if (Input::IsKeyDown(GLFW_KEY_O))
			{
				SceneManager::s_loadScene("scorestate");
			}
			else if (Input::IsKeyDown(GLFW_KEY_P))
			{
				SceneManager::s_loadScene("mainmenustate");
			}

			if (Input::IsKeyDown(GLFW_KEY_B))
			{
				SceneManager::s_loadScene("initstate", SceneManager::LoadSceneMode::Additive);
			}
			else if (Input::IsKeyDown(GLFW_KEY_N))
			{
				SceneManager::s_loadScene("scorestate",SceneManager::LoadSceneMode::Additive);
			}
			else if (Input::IsKeyDown(GLFW_KEY_M))
			{
				SceneManager::s_loadScene("mainmenustate", SceneManager::LoadSceneMode::Additive);
			}



			if (Input::IsKeyDown(GLFW_KEY_T))
			{
				SceneManager::s_unloadScene("initstate");
			}
			else if (Input::IsKeyDown(GLFW_KEY_Y))
			{
				SceneManager::s_unloadScene("scorestate");
			}
			else if (Input::IsKeyDown(GLFW_KEY_U))
			{
				SceneManager::s_unloadScene("mainmenustate");
			}

			if (Input::IsKeyDown(GLFW_KEY_L))
			{
				SceneManager::s_logAllActiveSceneNames();
			}
		}

		void Game::onLateUpdate(const float a_fDeltaTime)
		{
		
		}

		void Game::renderFrame()
		{
			m_pSceneManager->renderActiveScenes();
		}
	}
}