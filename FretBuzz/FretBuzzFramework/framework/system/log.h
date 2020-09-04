#pragma once

#include <memory>
#include <spdlog/spdlog.h>

namespace FRETBUZZ
{
	class Log
	{
	private:
		//singleton instance
		static Log* s_pInstance;

		//Logger for the engine
		static std::shared_ptr<spdlog::logger> s_EngineLogger;

		//Logger for the application
		static std::shared_ptr<spdlog::logger> s_AppLogger;

		Log();
		~Log();

	public:
		static Log* initialize();
		void destroy();

		static std::shared_ptr<spdlog::logger> GetEngineLogger() { return s_EngineLogger; };
		static std::shared_ptr<spdlog::logger>	GetAppLogger() { return s_AppLogger; };
	};

	// Engine loggine macros
	#define ENGINE_TRACE(...)		::FRETBUZZ::Log::GetEngineLogger()->trace(__VA_ARGS__)
	#define ENGINE_INFO(...)		::FRETBUZZ::Log::GetEngineLogger()->info(__VA_ARGS__)
	#define ENGINE_WARN(...)		::FRETBUZZ::Log::GetEngineLogger()->warn(__VA_ARGS__)
	#define ENGINE_ERROR(...)		::FRETBUZZ::Log::GetEngineLogger()->error(__VA_ARGS__)
	#define ENGINE_CRITICAL(...)	::FRETBUZZ::Log::GetEngineLogger()->critical(__VA_ARGS__)
												 
	// Client App logging macros				 
	#define APP_TRACE(...)			::FRETBUZZ::Log::GetAppLogger()->trace(__VA_ARGS__)
	#define APP_INFO(...)			::FRETBUZZ::Log::GetAppLogger()->info(__VA_ARGS__)
	#define APP_WARN(...)			::FRETBUZZ::Log::GetAppLogger()->warn(__VA_ARGS__)
	#define APP_ERROR(...)			::FRETBUZZ::Log::GetAppLogger()->error(__VA_ARGS__)
	#define APP_CRITICAL(...)		::FRETBUZZ::Log::GetAppLogger()->critical(__VA_ARGS__)
}