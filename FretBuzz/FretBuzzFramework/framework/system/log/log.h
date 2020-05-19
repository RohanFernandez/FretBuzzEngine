#pragma once

#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace ns_fretBuzz
{
	namespace ns_system
	{
		class FRETBUZZ_API Log
		{
		private:
			//singleton instance
			static Log* s_pInstance;

			//Logger for the engine
			static std::shared_ptr<spdlog::logger> s_Engine;

			//Logger for the application
			static std::shared_ptr<spdlog::logger> s_Application;

			Log();
			~Log();

		public:
			static Log* initialize();
			void destroy();
		};
	}
}