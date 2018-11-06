#pragma once
#include "framework\system\core\system.h"
#include "../../scenes/init_state.h"
#include "../../scenes/mainmenu_state.h"
#include "../../scenes/score_state.h"
#include "../../scenes/threed_test_setup.h"

int main()
{
	std::vector<ns_fretBuzz::ns_system::ISceneData*> l_vectScenes = 
	{
		new ns_fretBuzz::ns_system::SceneData<ns_fretBuzz::threed_test_scene>("3d_Test"),
		new ns_fretBuzz::ns_system::SceneData<ns_fretBuzz::InitState>("initstate")
		/*new SceneData<MainMenuState>("mainmenustate"),
		new SceneData<ScoreState>("scorestate")*/

	};

	ns_fretBuzz::ns_system::System::run(l_vectScenes);

	system("pause");
	return 0;
}