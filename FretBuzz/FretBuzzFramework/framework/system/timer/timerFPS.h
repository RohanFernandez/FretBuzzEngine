#pragma once
#include "timer.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		class TimerFPS : public Timer
		{
		private:
			static TimerFPS* s_pInstance;

			unsigned int m_iCurrentFPS = 0;
			unsigned int m_iLastFPSPerSec = 0;
			float m_fTimeElapsedInSecond = 0.0f;
			static constexpr float ONE_SECOND = 1.0f;
			bool m_bPrintFPS = false;

			TimerFPS(bool a_bIsPrintFPS = false);
			~TimerFPS();

		public:

			static TimerFPS* Initialize();
			void destroy();

			//calculates the delta time
			virtual void update() override;

			//gets the FPS
			unsigned int getFPS() const;

			//prints fps, can be set via constructor
			void PrintFPS(bool a_bIsPrint = true);
		};
	}
}