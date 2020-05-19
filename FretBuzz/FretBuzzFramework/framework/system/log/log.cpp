#include <fretbuzz_pch.h>
#include "log.h"
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

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
			std::vector<spdlog::sink_ptr> logSinks;
			logSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
			logSinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("FretBuzz.log", true));

			logSinks[0]->set_pattern("%^[%T] %n: %v%$");
			logSinks[1]->set_pattern("[%T] [%l] %n: %v");

			s_Engine = std::make_shared<spdlog::logger>("FretBuzz", begin(logSinks), end(logSinks));
			spdlog::register_logger(s_Engine);
			s_Engine->set_level(spdlog::level::trace);
			s_Engine->flush_on(spdlog::level::trace);

			s_Application = std::make_shared<spdlog::logger>("Application", begin(logSinks), end(logSinks));
			spdlog::register_logger(s_Application);
			s_Application->set_level(spdlog::level::trace);
			s_Application->flush_on(spdlog::level::trace);
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