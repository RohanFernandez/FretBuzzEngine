#pragma once

#include "../timer/timerFPS.h"
#include "audio_engine.h"
#include "master_renderer.h"
#include "input.h"
#include "resource_manager.h"
#include "physics_engine.h"
#include "../scene_manager.h"


namespace ns_fretBuzz
{
	namespace ns_system
	{
		class System
		{
		private:
			//Singleton instance pointer
			static System* s_pInstance;

			System();

			static const int START_SCREEN_WIDTH;
			static const int START_SCREEN_HEIGHT;
			static const std::string WINDOW_NAME;

			//Initializes the system, is called only once on startup
			static bool isInitialized();

			//Destroys components if failed to initialize and provides cleanup
			static void destroy();

			AudioEngine* m_pAudioEngine = nullptr;

			ns_graphics::MasterRenderer* m_pMasterRenderer = nullptr;

			Input* m_pInput = nullptr;

			//Main resource manager
			ResourceManager* m_pResourceManager = nullptr;

			PhysicsEngine* m_pPhysicsEngine = nullptr;

			std::vector<ISceneData*> m_vectScenes;
			SceneManager* m_pSceneManager = nullptr;

		public:
			~System();

			//Runs the main loop, initializes system publicly if not previusly initialized
			static void run();
			static void close();
		};
	}
}