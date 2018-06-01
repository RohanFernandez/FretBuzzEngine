#pragma once
#include "window.h"
#include "timer.h"
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

			//Initializes the system, is called only once on startup
			static bool initialize();

			//Destroys components if failed to initialize and provides cleanup
			static void destroy();

			Window* m_pWindow = nullptr;
			Input* m_pInput = nullptr;

		public:
			~System();

			//Runs the main loop, initializes system publicly if not previusly initialized
			static void Run();
		};
	}
}