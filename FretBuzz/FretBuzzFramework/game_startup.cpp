#include <fretbuzz_pch.h>
#include "scene_manager.h"
#include "game_startup.h"
#include <system.h>

namespace FRETBUZZ
{
	void GameStartup::run()
	{
		System::run(*this);
	}
}