#pragma once
#include "../../system/managers/scene_manager.h"

namespace ns_fretBuzz
{
	class ScoreState 
		: public ns_system::IScene,
		  public ns_system::IUpdateTimer
	{
	public:
		ScoreState(std::string a_strSceneName) :
			IScene(a_strSceneName),
			ns_system::IUpdateTimer()
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

		virtual void render() override
		{

		}
	};
}