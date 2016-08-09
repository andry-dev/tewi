#ifndef LOG_H
#define LOG_H

#include <exception>
#include <string>
#include <iostream>

#include <SDL2/SDL.h>

namespace tewi
{
	namespace Log
	{
		inline void warning(const std::string& str)
		{
			std::cout << "[W] " + str << '\n';
		}

		inline void error(const std::string& str)
		{
			std::cerr << "[E] " + str << '\n';
		}

		inline void info(const std::string& str)
		{
			std::cout << "[I] " + str << '\n';
		}

#ifndef NDEBUG
		#define Expects(cond, msg) \
			if (!(cond)) { \
				Log::error(msg); \
				SDL_Quit();  \
				std::terminate(); \
			}
		
		#define Ensures(cond, msg) \
			if (!(cond)) { \
				Log::error(msg); \
				SDL_Quit();  \
				std::terminate(); \
			}

		#define Loge(msg) \
			Log::error(msg);
		#define Logw(msg) \
			Log::warning(msg);
		#define Logi(msg) \
			Log::info(msg);
#else
		#define Expects(cond, msg)
		#define Ensures(cond, msg)
		#define Loge(msg)
		#define Logw(msg)
		#define Logi(msg)
#endif

#define STRINGIFY(x) #x
	}
}

#endif /* LOG_H */
