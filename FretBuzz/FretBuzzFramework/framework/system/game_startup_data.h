#pragma once
#include <vector>
#include "scene_manager.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		struct GameStartupData
		{
			std::vector<ns_fretBuzz::ns_system::ISceneData*> m_vectScenes;
			unsigned int m_uiScreenWidth, m_uiScreenHeight;
			std::string m_strWindowName;
		};
	}
}