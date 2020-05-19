#include <fretbuzz_pch.h>
#include "log.h"

namespace ns_fretBuzz
{
	namespace ns_system
	{
		//singleton instance
		Log* Log::s_pInstance = nullptr;

		//Logger for the engine
		std::shared_ptr<spdlog::logger> Log::s_Engine;
		//Logger for the application
		std::shared_ptr<spdlog::logger> Log::s_Application;

		Log::Log()
		{
			s_Engine = spdlog::stdout_color_mt("FretBuzz");
			s_Application = spdlog::stdout_color_mt("Application");
		}

		Log::~Log()
		{

		}

		Log* Log::initialize()
		{
			if (s_pInstance != nullptr)
			{
				return nullptr;
			}
			s_pInstance = new Log();
			return s_pInstance;
		}

		void Log::destroy()
		{
			delete s_pInstance;
			s_pInstance = nullptr;
		}
	}
}