#pragma once
#include <system/scene_manager.h>

namespace ns_HMGame
{
	class GameplayScene : public ns_fretBuzz::ns_system::IScene
	{
	public:
		GameplayScene(std::string a_strSceneName);
	};
}