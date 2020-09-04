#pragma once

namespace FRETBUZZ
{
	class ISceneData;
	struct  GameStartup
	{
		std::vector<ISceneData*> m_vectScenes;
		std::vector<std::string> m_vectLayers;
		unsigned int m_uiScreenWidth, m_uiScreenHeight;
		std::string m_strWindowName;

		void run();
	};
}