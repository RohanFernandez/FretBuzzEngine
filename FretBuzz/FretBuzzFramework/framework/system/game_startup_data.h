#pragma once
#include "scene_manager.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		struct FRETBUZZ_API GameStartupData
		{
			std::vector<ns_fretBuzz::ns_system::ISceneData*> m_vectScenes;
			std::vector<std::string> m_vectLayers;
			unsigned int m_uiScreenWidth, m_uiScreenHeight;
			std::string m_strWindowName;
		};
	}
}