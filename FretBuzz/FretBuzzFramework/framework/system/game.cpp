#pragma once
#include "game.h"
#include "../../scenes/init_state.h"
#include "../../scenes/mainmenu_state.h"
#include "../../scenes/score_state.h"
#include "../../scenes/threed_test_setup.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		//singleton instance
		Game* Game::s_pInstance = nullptr;

		Game::Game()
		{
			m_vectScenes =
			{
				/*new SceneData<InitState>("initstate"),
				new SceneData<MainMenuState>("mainmenustate"),
				new SceneData<ScoreState>("scorestate")*/

				new SceneData<threed_test_scene>("3d_Test")
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

		Game* Game::intialize()
		{
			if (s_pInstance != nullptr)
			{
				std::cout << "Game::intialize:: Game already exists.\n";
				return nullptr;
			}
			s_pInstance = new Game();
			return s_pInstance;
		}

		void Game::destroy()
		{
			delete s_pInstance;
			s_pInstance = nullptr;
		}

		const Game* Game::get()
		{
			return s_pInstance;
		}

		void Game::updateScenes(float a_fDeltaTime)
		{
			///testing start
			/*if (Input::IsKeyDown(GLFW_KEY_I))
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
				SceneManager::s_loadScene("scorestate", SceneManager::LoadSceneMode::Additive);
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
			}*/

			if (Input::IsKeyDown(GLFW_KEY_L))
			{
				SceneManager::s_logAllActiveSceneNames();
			}

			if (Input::IsKeyPutDown(GLFW_KEY_Q))
			{
				SceneManager::printSceneHierarchy();
			}

			///testing end

			m_pSceneManager->updateActiveScenes(a_fDeltaTime);
		}

		void Game::renderFrame(const Camera& a_Camera)
		{
			m_pSceneManager->renderActiveScenes(a_Camera);
		}
	}
}