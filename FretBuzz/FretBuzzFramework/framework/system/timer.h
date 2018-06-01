#pragma once

namespace ns_fretBuzz
{
	namespace ns_system
	{
		class Timer
		{
		private:
			bool m_bIsInitialized = false;

			bool initialize();

		public:
			Timer();
			~Timer();

			inline bool isInitialized() const
			{
				return m_bIsInitialized;
			}
		};
	}
}