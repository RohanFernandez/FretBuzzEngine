#pragma once

namespace ns_fretBuzz
{
	namespace ns_graphics
	{
		class SpriteBatchRenderer
		{
		private:
			static SpriteBatchRenderer* s_pInstance;

		public:

			SpriteBatchRenderer();
			~SpriteBatchRenderer();
			
			static void submit();
			static void start();
			static void end();
			static void flush();
		};
	}
}