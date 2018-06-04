#pragma once
#include "../../managers/scene_manager.h"

namespace ns_fretBuzz
{
	class InitState : 
		public ns_manager::IScene, 
		public ns_manager::IUpdateTimer
	{
	public:
		InitState(std::string a_strSceneName) :
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
			/*std::cout << "Update :: InitState state\n";*/
		}

		virtual void onLateUpdate(const float a_fDeltaTime) override
		{
			/*std::cout << "LateUpdate :: InitState state\n";*/
		}
	};
}