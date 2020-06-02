#pragma once

#include <memory>
#include <spdlog/spdlog.h>

namespace ns_fretBuzz
{
	namespace ns_system
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
	}

	// Engine loggine macros
	#define ENGINE_TRACE(...)		::ns_fretBuzz::ns_system::Log::GetEngineLogger()->trace(__VA_ARGS__)
	#define ENGINE_INFO(...)		::ns_fretBuzz::ns_system::Log::GetEngineLogger()->info(__VA_ARGS__)
	#define ENGINE_WARN(...)		::ns_fretBuzz::ns_system::Log::GetEngineLogger()->warn(__VA_ARGS__)
	#define ENGINE_ERROR(...)		::ns_fretBuzz::ns_system::Log::GetEngineLogger()->error(__VA_ARGS__)
	#define ENGINE_CRITICAL(...)	::ns_fretBuzz::ns_system::Log::GetEngineLogger()->critical(__VA_ARGS__)

	// Client App logging macros
	#define APP_TRACE(...)			::ns_fretBuzz::ns_system::Log::GetAppLogger()->trace(__VA_ARGS__)
	#define APP_INFO(...)			::ns_fretBuzz::ns_system::Log::GetAppLogger()->info(__VA_ARGS__)
	#define APP_WARN(...)			::ns_fretBuzz::ns_system::Log::GetAppLogger()->warn(__VA_ARGS__)
	#define APP_ERROR(...)			::ns_fretBuzz::ns_system::Log::GetAppLogger()->error(__VA_ARGS__)
	#define APP_CRITICAL(...)		::ns_fretBuzz::ns_system::Log::GetAppLogger()->critical(__VA_ARGS__)
}