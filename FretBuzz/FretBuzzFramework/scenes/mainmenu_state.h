#pragma once
#include "framework/system/scene_manager.h"
#include "framework/system/game_object.h"
#include "test/CharacterTest.h"

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
	};
}