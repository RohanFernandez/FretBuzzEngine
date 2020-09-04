#include <fretbuzz.h>
#include "main.h"
#include "game/scenes/gameplay_scene.h"
#include "test/scenes/threed_test_setup.h"

void SetStartupData(FRETBUZZ::GameStartup& a_GameStartupData)
{
	a_GameStartupData.m_strWindowName = "FretBuzz";
	a_GameStartupData.m_uiScreenWidth = 1200;
	a_GameStartupData.m_uiScreenHeight = 900;
	a_GameStartupData.m_vectLayers = { "PLAYER", "ENEMY", "PICKUP", "BOUNDARY", "BULLET"};

	a_GameStartupData.m_vectScenes =
	{
		//new FRETBUZZ::SceneData<ns_HMGame::threed_test_scene>("3d_Test"),
		new FRETBUZZ::SceneData<ns_HMGame::GameplayScene>("GamePlay")
		/*new SceneData<MainMenuState>("mainmenustate"),
		new SceneData<ScoreState>("scorestate")*/
	};
}