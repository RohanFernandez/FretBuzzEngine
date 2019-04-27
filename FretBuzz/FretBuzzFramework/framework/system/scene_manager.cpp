#include <fretbuzz_pch.h>
#include "scene_manager.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		///singleton instance
		SceneManager* SceneManager:: s_pInstance = nullptr;

		SceneManager* SceneManager::initialize(std::vector<ISceneData*>& a_pVectIScene)
		{
			if (s_pInstance != nullptr)
			{
				std::cout << "SceneManager::initialize:: SceneManager instance has already been previously initialized\n";
				return nullptr;
			}
			s_pInstance = new SceneManager(a_pVectIScene);
			return s_pInstance;
		}

		const SceneManager* SceneManager:: get()
		{
			return s_pInstance;
		}

		void SceneManager::destroy()
		{
			delete s_pInstance;
			s_pInstance = nullptr;
		}

		SceneManager::SceneManager(ISceneData* a_pStartScene)
			: FSM<ISceneData>(a_pStartScene, false)
		{
			m_vectActiveStates.emplace_back(a_pStartScene);
		}

		SceneManager::SceneManager(std::vector<ISceneData*>& a_pVectIScene)
			: FSM<ISceneData>(a_pVectIScene, false)
		{
			m_vectActiveStates.emplace_back(a_pVectIScene[0]);
		}

		SceneManager::~SceneManager()
		{
			m_pCurrentState->OnStateExit();
			m_pCurrentState = nullptr;
			unloadAllScenes();
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

			m_pCurrentState = l_pRegisteredState;
			ISceneData* l_pCurrentScene = dynamic_cast<ISceneData*>(m_pCurrentState);

			bool l_bCurrentSceneActive = l_pCurrentScene->isSceneLoaded();
			m_pCurrentState->OnStateEnter();

			///sets all dont destroy game objects of the previously active states as a child of the current game object
			///unload all previous scenes
			if (m_CurrentLoadSceneMode == LoadSceneMode::Single)
			{
				///Check to see if new state already exist in active states, then unload all other states except new state.
				for (std::vector<ISceneData*>::const_iterator l_pCurrentSceneIterator = m_vectActiveStates.cbegin();
					l_pCurrentSceneIterator != m_vectActiveStates.cend();)
				{
					ISceneData* l_pCurrentISceneData = *l_pCurrentSceneIterator;
					if (l_pCurrentISceneData->getStateName().compare(a_strTransitionTo) == 0)
					{
						l_pCurrentSceneIterator++;
						continue;
					}
					l_pCurrentSceneIterator = m_vectActiveStates.erase(l_pCurrentSceneIterator);
					l_pCurrentISceneData->resetDontDestroyParent(*l_pCurrentScene);
					l_pCurrentISceneData->unloadSceneData();
				}
			}

			if (!l_bCurrentSceneActive)
			{
				m_vectActiveStates.emplace_back(dynamic_cast<ISceneData*>(m_pCurrentState));
			}
			else
			{
				/// if scene was created in this function i.e. was not in the active state list previously.
				/// put the newly added state( current state ) as the last iterator in the active state list.
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
			for (std::vector<ISceneData*>::iterator l_pCurrentScene = m_vectActiveStates.begin();
				l_pCurrentScene != m_vectActiveStates.end();
				)
			{
				ISceneData*& l_pCurrentISceneData = *l_pCurrentScene;
				l_pCurrentScene = m_vectActiveStates.erase(l_pCurrentScene);
				l_pCurrentISceneData->unloadSceneData();

				delete l_pCurrentISceneData;
				l_pCurrentISceneData = nullptr;
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

		void SceneManager::updateActiveScenes(float a_fDeltaTime)
		{
			int l_iActiveSceneCount = m_vectActiveStates.size();
			for (int l_iSceneIndex = 0; l_iSceneIndex < l_iActiveSceneCount; l_iSceneIndex++)
			{
				m_vectActiveStates[l_iSceneIndex]->update(a_fDeltaTime);
			}
		}

		///all scenes should have its object render calls via this function
		void SceneManager::renderActiveScenes(const ns_graphics::Camera& a_Camera)
		{
			int l_iActiveSceneCount = m_vectActiveStates.size();
			for (int l_iSceneIndex = 0; l_iSceneIndex < l_iActiveSceneCount; l_iSceneIndex++)
			{
				m_vectActiveStates[l_iSceneIndex]->render(a_Camera);
			}
		}

		void SceneManager::LogSceneHierarchy()
		{
			int l_iActiveSceneCount = s_pInstance->m_vectActiveStates.size();
			for (int l_iSceneIndex = 0; l_iSceneIndex < l_iActiveSceneCount; l_iSceneIndex++)
			{
				s_pInstance->m_vectActiveStates[l_iSceneIndex]->logHierarchy();
			}
		}
	}
}