#pragma once

#ifdef _IS_DEBUG
	#ifndef _IS_DEBUG_RENDERING
		#define _IS_DEBUG_RENDERING
	#endif
#endif

#ifdef _IS_PLATFORM_WINDOWS
	#ifdef _IS_FRETBUZZ_BUILD_DLL
		#define FRETBUZZ_API __declspec(dllexport)
	#else
		//#define FRETBUZZ_API __declspec(dllimport)
		#define FRETBUZZ_API
	#endif
#else
	#define FRETBUZZ_API
#endif