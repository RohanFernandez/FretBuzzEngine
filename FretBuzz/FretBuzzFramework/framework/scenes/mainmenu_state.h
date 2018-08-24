#pragma once
#include "../system/scene_manager.h"

namespace ns_fretBuzz
{
	class MainMenuState 
		: public ns_system::IScene
	{
	public:
		MainMenuState(std::string a_strSceneName) :
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

		//virtual void onUpdate(const float a_fDeltaTime) override
		//{
		//	/*std::cout << "Update :: MainMenuState state\n";*/
		//}

		//virtual void onLateUpdate(const float a_fDeltaTime) override
		//{
		//	/*std::cout << "LateUpdate :: MainMenuState state\n";*/
		//}

		/*virtual void render() override
		{

		}*/
	};
}