#pragma once

#include <cstdio>
#include <exception>
#include <string>

#include <tewi/Utils/Glfw.h>

#include "tewi/Common.h"

namespace tewi
{
    /** Log-related functions.
     *
     */
    namespace Log
    {

        inline TEWI_EXPORT void warning(const std::string& str)
        {
            std::printf("[W] %s\n", str.c_str());
        }

        inline TEWI_EXPORT void error(const std::string& str)
        {
            std::printf("[E] %s\n", str.c_str());
        }

        inline TEWI_EXPORT void info(const std::string& str)
        {
            std::printf("[I] %s\n", str.c_str());
        }

#ifndef NDEBUG
        inline TEWI_EXPORT void debugWarning(const std::string& str)
        {
            warning(str);
        }
#else
        inline TEWI_EXPORT void debugWarning(const std::string&) {}
#endif

#ifndef NDEBUG
        inline TEWI_EXPORT void debugError(const std::string& str)
        {
            error(str);
        }
#else
        inline TEWI_EXPORT void debugError(const std::string&) {}
#endif

#ifndef NDEBUG
        inline TEWI_EXPORT void debugInfo(const std::string& str)
        {
            info(str);
        }
#else
        inline TEWI_EXPORT void debugInfo(const std::string&) {}
#endif

#ifndef NDEBUG
        /** Define for my version of GSL's Expects.
         *
         * I should probably change it.
         */
#define TEWI_EXPECTS(cond, msg)                                                \
    if (!(cond))                                                               \
    {                                                                          \
        tewi::Log::error(msg);                                                 \
        std::printf("Assertion failed at line %d : %s\n", __LINE__, __FILE__); \
        std::terminate();                                                      \
    }

        /** Define for my version of GSL's Ensures.
         *
         * I should probably change it.
         */
#define TEWI_ENSURES(cond, msg)                                                \
    if (!(cond))                                                               \
    {                                                                          \
        tewi::Log::error(msg);                                                 \
        std::printf("Assertion failed at line %d : %s\n", __LINE__, __FILE__); \
        std::terminate();                                                      \
    }

#else

#define TEWI_EXPECTS(cond, msg)
#define TEWI_ENSURES(cond, msg)

#endif
    } // namespace Log
} // namespace tewi
