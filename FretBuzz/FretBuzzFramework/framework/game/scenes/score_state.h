#pragma once
#include "../../managers/SceneManager.h"

namespace ns_fretBuzz
{
	class ScoreState : public ns_manager::IScene
	{
	public:
		ScoreState(std::string a_strSceneName) :
			IScene(a_strSceneName)
		{
		}

		virtual void OnStateEnter() override
		{
			IScene::OnStateEnter();
		}

		virtual void OnStateExit() override
		{
			IScene::OnStateExit();
		}
	};
}