#pragma once
#include "window.h"
#include "timer/timerFPS.h"
#include "../game/game.h"
#include "../managers/update_manager.h"

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
			static bool initialize();

			//Destroys components if failed to initialize and provides cleanup
			static void destroy();

			Window* m_pWindow = nullptr;
			
			TimerFPS* m_pFPStimer = nullptr;

			Game* m_pGame = nullptr;

			ns_manager::UpdateManager* m_pUpdateManager = nullptr;

		public:
			~System();

			//Runs the main loop, initializes system publicly if not previusly initialized
			static void Run();
		};
	}
}