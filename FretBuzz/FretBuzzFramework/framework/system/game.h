#pragma once
#include "../system/scene_manager.h"
#include <vector>

namespace ns_fretBuzz
{
	namespace ns_system
	{
		class Game
		{
		private:
			//List of all the scenes present in the game.
			std::vector<ISceneData*> m_vectScenes;

			//The scene manage that manages the transitions between scenes.
			SceneManager* m_pSceneManager = nullptr;

		public:
			// Add game scenes here for scene management
			Game();

			~Game();

			//Updates all the active scenes
			void updateScenes(float a_fDeltaTime);

			//Renders the current active scenes
			void renderFrame(const Viewport& a_Camera);
		};
	}
}