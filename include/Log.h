#ifndef TEWI_LOG_H
#define TEWI_LOG_H

/** \file */

#include <exception>
#include <string>
#include <cstdio>

#include <GLFW/glfw3.h>

namespace tewi
{
	/** Log-related functions.
	 *
	 */
	namespace Log
	{

		/** Prints a warning.
		 *
		 */
		inline void warning(const std::string& str)
		{
			std::printf("[W] %s\n", str.c_str());
		}

		/** Prints an error.
		 *
		 */
		inline void error(const std::string& str)
		{
			std::printf("[E] %s\n", str.c_str());
		}

		/** Prints an informational message.
		 *
		 */
		inline void info(const std::string& str)
		{
			std::printf("[I] %s\n", str.c_str());
		}

		/** Non-macro debug-only version of \a warning().
		 *
		 */
		inline void debugWarning(const std::string& str)
		{
#ifndef NDEBUG
			warning(str);
#endif
		}

		/** Non-macro debug-only version of \a error().
		 *
		 */
		inline void debugError(const std::string& str)
		{
#ifndef NDEBUG
			error(str);
#endif
		}

		/** Non-macro debug-only version of \a info().
		 *
		 */
		inline void debugInfo(const std::string& str)
		{
#ifndef NDEBUG
			info(str);
#endif
		}

#ifndef NDEBUG
		/** Define for my version of GSL's Expects.
		 *
		 * I should probably change it.
		 */
#define Expects(cond, msg) \
		if (!(cond)) { \
			tewi::Log::error(msg); \
			glfwTerminate();  \
			std::terminate(); \
		}

		/** Define for my version of GSL's Ensures.
		 *
		 * I should probably change it.
		 */
#define Ensures(cond, msg) \
		if (!(cond)) { \
			tewi::Log::error(msg); \
			glfwTerminate();  \
			std::terminate(); \
		}

#else
#define Expects(cond, msg)
#define Ensures(cond, msg)
#endif
	}
}

#endif /* TEWI_LOG_H */
