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
			m_vectScenes = 
				{ 
						new SceneData<InitState>("initstate"),
						new SceneData<MainMenuState>("mainmenustate"),
						new SceneData<ScoreState>("scorestatestate") 
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
				m_pSceneManager->TransitionTo("initstate");
			}
			else if (Input::IsKeyDown(GLFW_KEY_S))
			{
				m_pSceneManager->TransitionTo("scorestatestate");
			}
			else if (Input::IsKeyDown(GLFW_KEY_M))
			{
				m_pSceneManager->TransitionTo("mainmenustate");
			}
		}

		void Game::onLateUpdate(const float a_fDeltaTime)
		{
		
		}
	}
}