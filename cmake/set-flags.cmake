if(MSVC)
    # Common
    target_compile_options(${PROJECT_NAME}
        PUBLIC
        /W4 /std:c++17 /permissive- /GR-
        $<$<CONFIG:RELEASE>:/Ob2 /Ot /sdl->)
else()
    # Common
    target_compile_options(${PROJECT_NAME}
        PRIVATE
        -Wall -Wextra -pedantic -Wpedantic
        -Wno-effc++ -Wno-unused-const-variable
        -pipe -fno-rtti)

    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        target_compile_options(${PROJECT_NAME}
            PRIVATE
            -Weverything -Wno-missing-prototypes)
    endif()

    target_compile_options(${PROJECT_NAME}
        PRIVATE
        $<$<CONFIG:RELEASE>:-O3>
        $<$<CONFIG:DEBUG>:-fno-omit-frame-pointer>)
endif()

if(WIN32)
    target_compile_definitions(${PROJECT_NAME}
        PRIVATE
        _CRT_SECURE_NO_WARNINGS=1)
endif()

if (TEWI_ENABLE_LTO)
    check_ipo_supported(RESULT TEWI_LTO_SUPPORT)
    if (TEWI_LTO_SUPPORT)
        message(STATUS "[tewi] LTO enabled")
        set_property(TARGET ${PROJECT_NAME}
            PROPERTY INTERPROCEDURAL_OPTIMIZATION TRUE)
    else()
        message(NOTICE " [tewi] LTO not supported by your compiler")
    endif()
endif()

set_target_properties(${PROJECT_NAME}
    PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON)

if (BUILD_SHARED_LIBS)
    message(STATUS "[tewi] Building as DLL/so")
    target_compile_definitions(${PROJECT_NAME}
        PUBLIC
        TEWI_SHARED_LIB=1
        GLEW_BUILD)
else()
    message(STATUS "[tewi] Building as LIB/a")
    target_compile_definitions(${PROJECT_NAME}
        PUBLIC
        TEWI_STATIC_LIB=1
        GLEW_STATIC)
endif()
