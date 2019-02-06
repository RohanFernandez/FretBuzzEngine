#pragma once

namespace ns_fretBuzz
{
	namespace ns_system
	{
		class Timer
		{
		protected:
			std::chrono::steady_clock::time_point m_CurrentTimePoint;
			std::chrono::steady_clock::time_point m_LastTimePoint;
			std::chrono::duration<float> m_fDuration;
			float m_fDeltaTime = 0.0f;

		public:
			Timer();
			virtual ~Timer();

			virtual void update();
			virtual float getDeltaTime() const;
		};
	}
}