#pragma once

#include "asl/types"
#include "asl/meta"

/** \file 
 * This is a common file used all over the project.
 * 
 */

#ifdef _WIN32
    #ifdef TEWI_STATIC_LIB
        #define TEWI_EXPORT
    #elif defined(TEWI_SHARED_LIB)
        #define TEWI_EXPORT __declspec(dllexport)
    #else
        #define TEWI_EXPORT __declspec(dllimport)
    #endif
#else
    #define TEWI_EXPORT
#endif

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


// Type traits
namespace tewi
{
    namespace detail
    {
        template <typename T, typename U>
        constexpr bool api_compatible_cond =
                (std::is_base_of<T, U>::value ||
                std::is_base_of<T, U>::value ||
                std::is_same<T, U>::value);
    }

    template <typename T, typename U, typename... Ts>
    struct is_api_compatible
    {
        constexpr static bool value =
            detail::api_compatible_cond<T, U> &&
            is_api_compatible<U, Ts...>::value;
    };

    template <typename T, typename U>
    struct is_api_compatible<T, U>
    {
        constexpr static bool value = detail::api_compatible_cond<T, U>;
    };
    
    template <typename... Ts>
    constexpr bool is_api_compatible_v = is_api_compatible<Ts...>::value;

    /** \brief Switches the API used for a type.
     *
     * If the APITag does not model Concept then the base API will be used, else
     * it will happily use APITag.
     *
     */
    template <typename APITag, bool Concept>
    struct switch_api
    {
        using type = typename std::conditional
                     <
                         Concept,
                         APITag,
                         typename APITag::base
                     >::type;
    };

} // namespace tewi
