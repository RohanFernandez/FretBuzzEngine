#pragma once

#include "timer/timerFPS.h"
#include "../game/game.h"
#include "audio_engine.h"
#include "master_renderer.h"
#include "input.h"

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

			Game* m_pGame = nullptr;

			AudioEngine* m_pAudioEngine = nullptr;

			MasterRenderer* m_pMasterRenderer = nullptr;

			Input* m_pInput = nullptr;

		public:
			~System();

			//Runs the main loop, initializes system publicly if not previusly initialized
			static void Run();
		};
	}
}