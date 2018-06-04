#pragma once
#include "../../managers/scene_manager.h"

namespace ns_fretBuzz
{
	class ScoreState 
		: public ns_manager::IScene,
		  public ns_manager::IUpdateTimer
	{
	public:
		ScoreState(std::string a_strSceneName) :
			IScene(a_strSceneName),
			ns_manager::IUpdateTimer()
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

		virtual void onUpdate(const float a_fDeltaTime) override
		{
			/*std::cout << "Update :: Running score state\n";*/
		}

		virtual void onLateUpdate(const float a_fDeltaTime) override
		{
			/*std::cout << "LateUpdate :: Running score state\n";*/
		}
	};
}