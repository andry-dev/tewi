#pragma once

#include "Utils/Types.h"
#include "Utils/Functional.h"

/** \file 
 * This is a common file for typedefs and useful functions.
 * 
 * \note The typedefs are **const by default**.
 */

// Detect game

#if __cplusplus == 201402L
	#define TEWI_CXX14_SUPPORTED 1
#elif __cplusplus > 201402L
	#define TEWI_CXX14_SUPPORTED 1
	#define TEWI_CXX17_SUPPORTED 1
#endif

#ifdef __has_include
	#if __has_include(<optional>)
		#define TEWI_CXX17_OPTIONAL 1
	#elif __has_include(<experimental/optional>)
		#define TEWI_CXX17_OPTIONAL 1
		#define TEWI_CXX17_OPTIONAL_EXPERIMENTAL
	#else
		#define TEWI_CXX17_OPTIONAL 0
	#endif

	#if __has_include(<filesystem>)
		#define TEWI_CXX17_FILESYSTEM 1
	#elif __has_include(<experimental/filesystem>)
		#define TEWI_CXX17_FILESYSTEM_EXPERIMENTAL
		#define TEWI_CXX17_FILESYSTEM 1
	#else
		#define TEWI_CXX17_FILESYSTEM 0
	#endif
#endif

#if defined(_WIN32)
	#define TEWI_WIN32
#elif defined(__unix__) || defined(__linux__) || (defined(__APPLE__) && defined(__MACH__))
	#define TEWI_POSIX
#else
	#define TEWI_UNKNOWN_PLATFORM
#endif
