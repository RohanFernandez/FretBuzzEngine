#pragma once
#include "game.h"
#include "../system/input.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		Game::Game()
		{
			using namespace ns_manager;
			m_vectStates = 
				{ 
						new SceneData<InitState>("initstate"),
						new SceneData<MainMenuState>("mainmenustate"),
						new SceneData<ScoreState>("scorestatestate") 
				};

			m_pSceneManager = new ns_manager::SceneManager(m_vectStates);
		}

		Game::~Game()
		{
			for (auto l_CurrentState = m_vectStates.cbegin(), l_EndStateIndex = m_vectStates.cend();
				l_CurrentState != l_EndStateIndex; l_CurrentState++)
			{
				delete *l_CurrentState;
			}

			if (m_pSceneManager != nullptr)
			{
				delete m_pSceneManager;
				m_pSceneManager = nullptr;
			}
		}

		void Game::update(const float a_fDeltaTime)
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
	}
}