#pragma once
#include "scene_manager.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		SceneManager::SceneManager(ISceneData* a_pStartScene)
			: FSM<ISceneData>(a_pStartScene, false)
		{
			m_vectActiveStates.push_back(a_pStartScene);
		}

		SceneManager::SceneManager(std::vector<ISceneData*>& a_pVectIScene)
			: FSM<ISceneData>(a_pVectIScene, false)
		{
			m_vectActiveStates.push_back(a_pVectIScene[0]);
		}

		SceneManager::~SceneManager()
		{
			m_pCurrentState->OnStateExit();
			m_pCurrentState = nullptr;
			unloadAllScenes();

		}

		void SceneManager::registerState(ISceneData* a_pScene)
		{
			FSM<ISceneData>::RegisterState(a_pScene);
		}

		void SceneManager::loadScene(std::string a_strSceneName, LoadSceneMode a_LoadSceneMode)
		{
			m_CurrentLoadSceneMode = a_LoadSceneMode;
			transitionTo(a_strSceneName);
		}

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
				++l_pCurrentScene
				)
			{
				if (l_pRegisteredState == *l_pCurrentScene)
				{
					m_vectActiveStates.erase(l_pCurrentScene);
					(*l_pCurrentScene)->unloadSceneData();
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
			bool l_bCurrentSceneActive = l_pCurrentScene->isSceneActive();

			m_pCurrentState->OnStateEnter();

			if (!l_bCurrentSceneActive)
			{
				m_vectActiveStates.push_back(dynamic_cast<ISceneData*>(m_pCurrentState));
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
	}
}