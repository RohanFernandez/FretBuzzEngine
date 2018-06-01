#pragma once

namespace ns_fretBuzz
{
	namespace ns_system
	{
		class Input
		{
		private:
			bool m_bIsInitialized = true;

		public:
			Input();
			~Input();

			inline bool isInitialized() const
			{
				return m_bIsInitialized;
			}
		};
	}
}