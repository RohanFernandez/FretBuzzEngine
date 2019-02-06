#include <fretbuzz_pch.h>
#include "system/game_startup_data.h"
#include "system/core/system.h"
#include "scenes/init_state.h"
#include "scenes/mainmenu_state.h"
#include "scenes/score_state.h"
#include "scenes/threed_test_setup.h"

int main()
{
	ns_fretBuzz::ns_system::GameStartupData m_GameStartupData;
	m_GameStartupData.m_strWindowName = "FretBuzz";
	m_GameStartupData.m_uiScreenWidth = 800;
	m_GameStartupData.m_uiScreenHeight = 600;
	m_GameStartupData.m_vectScenes = 
	{
		//new ns_fretBuzz::ns_system::SceneData<ns_fretBuzz::threed_test_scene>("3d_Test"),
		new ns_fretBuzz::ns_system::SceneData<ns_fretBuzz::InitState>("initstate")
		/*new SceneData<MainMenuState>("mainmenustate"),
		new SceneData<ScoreState>("scorestate")*/
	};

	ns_fretBuzz::ns_system::System::run(m_GameStartupData);

	return 0;
}