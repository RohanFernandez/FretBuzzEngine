#include <fretbuzz_pch.h>
#include "log.h"
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace FRETBUZZ
{
	//singleton instance
	Log* Log::s_pInstance = nullptr;

	//Logger for the engine
	std::shared_ptr<spdlog::logger> Log::s_EngineLogger;
	//Logger for the application
	std::shared_ptr<spdlog::logger> Log::s_AppLogger;

	Log::Log()
	{
		std::vector<spdlog::sink_ptr> logSinks;
		logSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
		logSinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("FretBuzz.log", true));

		logSinks[0]->set_pattern("%^[%T] %n: %v%$");
		logSinks[1]->set_pattern("[%T] [%l] %n: %v");

		s_EngineLogger = std::make_shared<spdlog::logger>("FretBuzz", begin(logSinks), end(logSinks));
		spdlog::register_logger(s_EngineLogger);
		s_EngineLogger->set_level(spdlog::level::trace);
		s_EngineLogger->flush_on(spdlog::level::trace);

		s_AppLogger = std::make_shared<spdlog::logger>("Application", begin(logSinks), end(logSinks));
		spdlog::register_logger(s_AppLogger);
		s_AppLogger->set_level(spdlog::level::trace);
		s_AppLogger->flush_on(spdlog::level::trace);
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