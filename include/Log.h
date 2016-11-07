#ifndef LOG_H
#define LOG_H

#include <exception>
#include <string>
#include <cstdio>

#include <GLFW/glfw3.h>

namespace tewi
{
	namespace Log
	{
		inline void warning(const std::string& str)
		{
			std::printf("[W] %s\n", str.c_str());
		}

		inline void error(const std::string& str)
		{
			std::printf("[E] %s\n", str.c_str());
		}

		inline void info(const std::string& str)
		{
			std::printf("[I] %s\n", str.c_str());
		}

		inline void debugWarning(const std::string& str)
		{
			#ifndef NDEBUG
			warning(str);
			#endif
		}

		inline void debugError(const std::string& str)
		{
			#ifndef NDEBUG
			error(str);
			#endif
		}

		inline void debugInfo(const std::string& str)
		{
			#ifndef NDEBUG
			info(str);
			#endif
		}

#ifndef NDEBUG
		#define Expects(cond, msg) \
			if (!(cond)) { \
				tewi::Log::error(msg); \
				glfwTerminate();  \
				std::terminate(); \
			}
		
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

#endif /* LOG_H */
