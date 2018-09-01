#pragma once
#include "../system/scene_manager.h"
#include "../system/game_object.h"
#include "../test/CharacterTest.h"

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

		virtual ~MainMenuState()
		{}
	};
}