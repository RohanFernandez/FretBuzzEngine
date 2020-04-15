#pragma once
#include "utils/Event/Delegate/delegate.h"

namespace ns_fretBuzz
{
	namespace ns_editor
	{
		class FRETBUZZ_API Inspector
		{
		private:
			static Inspector* s_pInstance;

			Inspector();
			~Inspector();

		public:
			static Inspector* initialize();
			void destroy();
			void render(int a_iFPS);
		};
	}
}