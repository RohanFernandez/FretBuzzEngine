#include <fretbuzz.h>
#include "main.h"
#include "game/scenes/gameplay_scene.h"
#include "test/scenes/threed_test_setup.h"

void SetStartupData(ns_fretBuzz::ns_system::GameStartup& a_GameStartupData)
{
	a_GameStartupData.m_strWindowName = "FretBuzz";
	a_GameStartupData.m_uiScreenWidth = 1200;
	a_GameStartupData.m_uiScreenHeight = 900;
	a_GameStartupData.m_vectLayers = {"Enemy", "Player", "Walls", "Bullets", "Drops", "layercube"};
	a_GameStartupData.m_vectScenes =
	{
		//new ns_fretBuzz::ns_system::SceneData<ns_HMGame::threed_test_scene>("3d_Test"),
		new ns_fretBuzz::ns_system::SceneData<ns_HMGame::GameplayScene>("GamePlay")
		/*new SceneData<MainMenuState>("mainmenustate"),
		new SceneData<ScoreState>("scorestate")*/
	};
}