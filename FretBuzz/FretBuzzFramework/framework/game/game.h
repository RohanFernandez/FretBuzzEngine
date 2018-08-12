#pragma once
#include "../system/managers/scene_manager.h"
#include "../system/managers/update_manager.h"
#include "../system/managers/resource_manager.h"
#include "scenes/init_state.h"
#include "scenes/mainmenu_state.h"
#include "scenes/score_state.h"
#include <vector>

#include "../graphics/shader.h"
#include "../graphics/texture.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		class Game : public IUpdateTimer
		{
		private:
			//List of all the scenes present in the game.
			std::vector<ISceneData*> m_vectScenes;

			//The scene manage that manages the transitions between scenes.
			SceneManager* m_pSceneManager = nullptr;

			//Main resource manager
			ResourceManager* m_pResourceManager = nullptr;

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