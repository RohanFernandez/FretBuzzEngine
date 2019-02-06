#include <fretbuzz_pch.h>
#include "timer.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		Timer::Timer()
			: m_CurrentTimePoint{ std::chrono::steady_clock::now() },
			m_LastTimePoint{ std::chrono::steady_clock::now() }
		{

		}

		void Timer::update()
		{
			m_CurrentTimePoint = std::chrono::steady_clock::now();
			m_fDuration = m_CurrentTimePoint - m_LastTimePoint;
			m_LastTimePoint = m_CurrentTimePoint;
			m_fDeltaTime = m_fDuration.count();
		}

		float Timer::getDeltaTime() const
		{
			return m_fDeltaTime;
		}

		Timer::~Timer()
		{

		}
	}
}