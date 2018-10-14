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
			static Game* s_pInstance;

			//List of all the scenes present in the game.
			std::vector<ISceneData*> m_vectScenes;

			//The scene manager that manages the transitions between scenes.
			SceneManager* m_pSceneManager = nullptr;

			// Add game scenes here for scene management
			Game();
			~Game();

		public:
			static Game* intialize();
			void destroy();
			static const Game* get();

			//Updates all the active scenes
			void updateScenes(float a_fDeltaTime);

			//Renders the current active scenes
			void renderFrame(const ns_graphics::Camera& a_Camera);
		};
	}
}