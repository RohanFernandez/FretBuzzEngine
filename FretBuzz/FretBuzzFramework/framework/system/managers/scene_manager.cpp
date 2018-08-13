#pragma once
#include "scene_manager.h"
#include <algorithm>

namespace ns_fretBuzz
{
	namespace ns_system
	{
		///singleton instance
		SceneManager* SceneManager:: s_pInstance = nullptr;

		SceneManager::SceneManager(ISceneData* a_pStartScene)
			: FSM<ISceneData>(a_pStartScene, false)
		{
			if (s_pInstance != nullptr)
			{
				return;
			}
			s_pInstance = this;
			m_vectActiveStates.push_back(a_pStartScene);
		}

		SceneManager::SceneManager(std::vector<ISceneData*>& a_pVectIScene)
			: FSM<ISceneData>(a_pVectIScene, false)
		{
			if (s_pInstance != nullptr)
			{
				return;
			}
			s_pInstance = this;
			m_vectActiveStates.push_back(a_pVectIScene[0]);
		}

		SceneManager::~SceneManager()
		{
			if (s_pInstance != this)
			{
				return;
			}

			m_pCurrentState->OnStateExit();
			m_pCurrentState = nullptr;
			unloadAllScenes();

			s_pInstance = nullptr;	
		}

		void SceneManager::s_registerState(ISceneData* a_pScene)
		{
			s_pInstance->registerState(a_pScene);
		}

		void SceneManager::s_loadScene(std::string a_strSceneName, SceneManager::LoadSceneMode a_LoadSceneMode)
		{
			s_pInstance->loadScene(a_strSceneName, a_LoadSceneMode);
		}

		void SceneManager::s_unloadScene(std::string a_strSceneName)
		{
			s_pInstance->unloadScene(a_strSceneName);
		}

		void SceneManager::s_logAllActiveSceneNames()
		{
			s_pInstance->logAllActiveSceneNames();
		}

		///Registers the state into the list of state that will able to transition to.
		void SceneManager::registerState(ISceneData* a_pScene)
		{
			FSM<ISceneData>::RegisterState(a_pScene);
		}

		///Loads the scene if not already included in the active scene container.
		///Sets it as the current scene.
		void SceneManager::loadScene(std::string a_strSceneName, LoadSceneMode a_LoadSceneMode)
		{
			m_CurrentLoadSceneMode = a_LoadSceneMode;
			transitionTo(a_strSceneName);
		}

		///Unloads the scene and removes the scene from the active scene container.
		void SceneManager::unloadScene(std::string a_strSceneName)
		{
			IFSM* l_pRegisteredState = getStateRegisteredWithID(a_strSceneName);
			if (l_pRegisteredState == m_pCurrentState || 
				l_pRegisteredState == nullptr)
			{
				return;
			}

			for (std::vector<ISceneData*>::iterator l_pCurrentScene = m_vectActiveStates.begin(),
				l_pEndState = m_vectActiveStates.end();
				l_pCurrentScene != l_pEndState;
				l_pCurrentScene++
				)
			{
				if (l_pRegisteredState == *l_pCurrentScene)
				{
					l_pCurrentScene = m_vectActiveStates.erase(l_pCurrentScene);
					dynamic_cast<ISceneData*>(l_pRegisteredState)->unloadSceneData();
					return;
				}
			}
		}

		void SceneManager::transitionTo(std::string a_strTransitionTo)
		{
			IFSM* l_pRegisteredState = getStateRegisteredWithID(a_strTransitionTo);
			if (l_pRegisteredState == nullptr)
			{
				std::cout << "FSM::RegisterState:: State with name '" << a_strTransitionTo << "' does not exist in the state list.\n";
				return;
			}

			if (l_pRegisteredState == m_pCurrentState)
			{
				return;
			}

			m_pCurrentState->OnStateExit();

			if (m_CurrentLoadSceneMode == LoadSceneMode::Single)
			{
				unloadAllScenes();
			}

			m_pCurrentState = l_pRegisteredState;
			ISceneData* l_pCurrentScene = dynamic_cast<ISceneData*>(m_pCurrentState);

			bool l_bCurrentSceneActive = l_pCurrentScene->isSceneLoaded();

			m_pCurrentState->OnStateEnter();

			if (!l_bCurrentSceneActive)
			{
				m_vectActiveStates.push_back(dynamic_cast<ISceneData*>(m_pCurrentState));
			}
			else
			{
				int l_iActiveSceneCount = m_vectActiveStates.size();
				int l_iCurrentScenePosition = 0;

				for (; l_iCurrentScenePosition < l_iActiveSceneCount; l_iCurrentScenePosition++)
				{
					if (m_vectActiveStates[l_iCurrentScenePosition] == l_pCurrentScene)
					{
						l_iCurrentScenePosition = l_iCurrentScenePosition;
						break;
					}
				}

				std::iter_swap(m_vectActiveStates.begin() + l_iCurrentScenePosition, m_vectActiveStates.end() - 1);
			}
		}

		///Removes all stored scenes from the AvtiveScenes container
		///Deletes the scene from memory
		void SceneManager::unloadAllScenes()
		{
			for (std::vector<ISceneData*>::const_iterator l_pCurrentScene = m_vectActiveStates.cbegin();
				l_pCurrentScene != m_vectActiveStates.cend();
				)
			{
				ISceneData* l_pCurrentISceneData = *l_pCurrentScene;
				l_pCurrentScene = m_vectActiveStates.erase(l_pCurrentScene);
				l_pCurrentISceneData->unloadSceneData();
			}
		}

		///Logs all active scene with its names
		void SceneManager::logAllActiveSceneNames()
		{
			int l_iStateIndex = 0;
			for (std::vector<ISceneData*>::iterator l_pCurrentScene = m_vectActiveStates.begin(),
				l_pEndState = m_vectActiveStates.end();
				l_pCurrentScene != l_pEndState;
				l_pCurrentScene++, l_iStateIndex++
				)
			{
				if ((*l_pCurrentScene) == m_pCurrentState)
				{
					std::cout <<l_iStateIndex << " Current Active state :: " << (*l_pCurrentScene)->getStateName()<< "\n";
				}
				else
				{
					std::cout << l_iStateIndex << " Active state :: " << (*l_pCurrentScene)->getStateName() << "\n";
				}
			}
		}

		///all scenes should have its object render calls via this function
		void SceneManager::renderActiveScenes()
		{
			int l_iActiveSceneCount = m_vectActiveStates.size();
			for (int l_iSceneIndex = 0; l_iSceneIndex < l_iActiveSceneCount; l_iSceneIndex++)
			{
				m_vectActiveStates[l_iSceneIndex]->render();
			}
		}
	}
}