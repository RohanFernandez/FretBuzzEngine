#include <fretbuzz_pch.h>
#include "scene_manager.h"
#include "game_startup.h"
#include "system/core/system.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		void GameStartup::run()
		{
			ns_fretBuzz::ns_system::System::run(*this);
		}
	}
}