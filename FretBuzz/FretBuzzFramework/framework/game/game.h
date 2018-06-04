#pragma once
#include "../managers/scene_manager.h"
#include "../managers/update_manager.h"
#include "scenes/init_state.h"
#include "scenes/mainmenu_state.h"
#include "scenes/score_state.h"
#include <vector>

namespace ns_fretBuzz
{
	namespace ns_system
	{
		class Game : public ns_manager::IUpdateTimer
		{
		private:
			//List of all the scenes present in the game.
			std::vector<ns_manager::ISceneData*> m_vectScenes;

			//The scene manage that manages the transitions between scenes.
			ns_manager::SceneManager* m_pSceneManager = nullptr;

		public:
			// Add game scenes here for scene management
			Game();

			~Game();

			//Updates the updatable objects and the common game functionality
			virtual void onUpdate(const float a_fDeltaTime) override;

			//Updates the updatable objects and the common game functionality
			virtual void onLateUpdate(const float a_fDeltaTime) override;
		};
	}
}