#include <fretbuzz_pch.h>
#include "timerFPS.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		TimerFPS::TimerFPS(bool a_bIsPrintFPS)
			: Timer(), 
			m_bPrintFPS{a_bIsPrintFPS}
		{
			
		}

		TimerFPS::~TimerFPS()
		{
			
		}

		void TimerFPS::update()
		{
			Timer::update();
			m_iCurrentFPS++;

			m_fTimeElapsedInSecond += m_fDeltaTime;

			if (m_fTimeElapsedInSecond >= ONE_SECOND)
			{
				m_fTimeElapsedInSecond -= ONE_SECOND;
				m_iLastFPSPerSec = m_iCurrentFPS;
				if (m_bPrintFPS)
				{
					std::cout << "TimerFPS::update::FPS::"<< m_iCurrentFPS<<"\n";
				}
				m_iCurrentFPS = 0;
			}
		}

		void TimerFPS::PrintFPS(bool a_bIsPrint)
		{
			m_bPrintFPS = a_bIsPrint;
		}

		unsigned int TimerFPS::getFPS() const
		{
			return m_iLastFPSPerSec;
		}
	}
}