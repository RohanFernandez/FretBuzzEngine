#pragma once
#include "timer.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		class FRETBUZZ_API TimerFPS : public Timer
		{
		private:
			unsigned int m_iCurrentFPS = 0;
			unsigned int m_iLastFPSPerSec = 0;
			float m_fTimeElapsedInSecond = 0.0f;
			static constexpr float ONE_SECOND = 1.0f;
			bool m_bPrintFPS = false;

		public:
			TimerFPS(bool a_bIsPrintFPS = false);
			~TimerFPS();

			//calculates the delta time
			virtual void update() override;

			//gets the FPS
			unsigned int getFPS() const;

			//prints fps, can be set via constructor
			void PrintFPS(bool a_bIsPrint = true);
		};
	}
}