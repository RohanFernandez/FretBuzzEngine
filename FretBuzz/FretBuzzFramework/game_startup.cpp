#include <fretbuzz_pch.h>
#include "scene_manager.h"
#include "game_startup.h"
#include <system.h>

namespace ns_fretBuzz
{
	void GameStartup::run()
	{
		System::run(*this);
	}
}