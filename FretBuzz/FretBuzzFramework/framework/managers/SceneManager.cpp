#pragma once
#include "SceneManager.h"

namespace ns_fretBuzz
{
	namespace ns_manager
	{
		SceneManager::SceneManager(ISceneData* a_pStartScene, bool a_bIsTransitionToSelfAllowed)
			: FSM<ISceneData>(a_pStartScene, a_bIsTransitionToSelfAllowed)
		{

		}

		SceneManager::SceneManager(std::vector<ISceneData*>& a_pVectIScene, bool a_bIsTransitionToSelfAllowed)
			: FSM<ISceneData>(a_pVectIScene, a_bIsTransitionToSelfAllowed)
		{

		}

		SceneManager::~SceneManager()
		{

		}

		void SceneManager::RegisterState(ISceneData* a_pScene)
		{
			FSM<ISceneData>::RegisterState(a_pScene);
		}

		void SceneManager::TransitionTo(std::string a_strSceneName)
		{
			FSM<ISceneData>::TransitionTo(a_strSceneName);
		}
	}
}