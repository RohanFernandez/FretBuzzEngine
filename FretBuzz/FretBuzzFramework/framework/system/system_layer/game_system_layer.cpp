#include <fretbuzz_pch.h>
#include "game_system_layer.h"

namespace ns_fretBuzz
{
	GameSystemLayer::GameSystemLayer()
		: SystemLayerBase("GAME")
	{
			
	}

	GameSystemLayer::~GameSystemLayer()
	{
	}

	void GameSystemLayer::update(const float& a_fDeltaTime, SceneManager& a_SceneManager)
	{
		a_SceneManager.updateActiveScenes(a_fDeltaTime);
	}

	void GameSystemLayer::lateUpdate(const float& a_fDeltaTime, SceneManager& a_SceneManager)
	{
		a_SceneManager.lateUpdateActiveScenes(a_fDeltaTime);
	}

	void GameSystemLayer::render(SceneManager& a_SceneManager)
	{
		//a_SceneManager.renderActiveScenes(a_fDeltaTime);
	}
}