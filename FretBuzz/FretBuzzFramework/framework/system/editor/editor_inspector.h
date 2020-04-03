#pragma once
#include "utils/Event/Delegate/delegate.h"

namespace ns_fretBuzz
{
	namespace ns_editor
	{
		class doClass
		{
		public:
			int printThis1(int)
			{
				std::cout << "Printing 111 ... member func\n";
				return 0;
			}

			int printThis2(int) const
			{
				std::cout << "Printing 222 ... const member func\n";
				return 0;
			}

			static int printThis3(int)
			{
				std::cout << "Printing 333 ... static member func\n";
				return 0;
			}
		};

		class FRETBUZZ_API Inspector
		{
		private:
			static Inspector* s_pInstance;

			Inspector();
			~Inspector();

			int m_iActionRemoveCount = 0;

			ns_fretBuzz::Delegate<int(int)> fuzzDele;
			doClass testDoClass;

		public:
			static Inspector* initialize();
			void destroy();
			void render(int a_iFPS);
		};
	}
}