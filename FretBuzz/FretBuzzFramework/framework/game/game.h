#pragma once
#include "../managers/SceneManager.h"
#include "scenes\init_state.h"
#include "scenes\mainmenu_state.h"
#include "scenes\score_state.h"
#include <vector>

namespace ns_fretBuzz
{
	namespace ns_system
	{
		class Game
		{
		private:
			//List of all the states present in the game.
			std::vector<ns_manager::ISceneData*> m_vectStates;

			//The scene manage that manages the transitions between scenes.
			ns_manager::SceneManager* m_pSceneManager = nullptr;

		public:
			Game();
			~Game();

			//Updates the updatable objects and the common game functionality
			void update(const float a_fDeltaTime);
		};
	}
}