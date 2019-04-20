if (TEWI_INTEGRATE_IMGUI)
    file(GLOB test-imguidir imgui/imgui*)
    if (test-imguidir)
        set(FOUND_LOCAL_IMGUI 1 PARENT_SCOPE)
        add_library(ImGui STATIC
                    imgui/imgui.cpp
                    imgui/imgui_draw.cpp
                    imgui/imgui_widgets.cpp
                    imgui/misc/cpp/imgui_stdlib.cpp)
        target_include_directories(ImGui SYSTEM PUBLIC imgui/ imgui/misc/cpp/)

        message(STATUS "[tewi] Found local imgui in external/imgui")
    else()
        set(FOUND_LOCAL_IMGUI 0 PARENT_SCOPE)
    endif()
endif()

file(GLOB test-glfwdir glfw/CMakeLists.txt)
if (test-glfwdir)
    set(FOUND_LOCAL_GLFW 1 PARENT_SCOPE)

    set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

    add_subdirectory(glfw)
    add_library(glfw::glfw ALIAS glfw) 

    message(STATUS "[tewi] Found local glfw in external/glfw")
else()
    set(FOUND_LOCAL_GLFW 0 PARENT_SCOPE)
endif()

file(GLOB test-glmdir glm/CMakeLists.txt)
if (test-glmdir)
    SET(FOUND_LOCAL_GLM 1 PARENT_SCOPE)

    set(GLM_TEST_ENABLE OFF CACHE BOOL "" FORCE)
    set(GLM_TEST_ENABLE_FAST_MATH OFF CACHE BOOL "" FORCE)

    add_subdirectory(glm)

    add_library(glm::glm ALIAS glm) 

    message(STATUS "[tewi] Found local glm in external/glm")
else()
    SET(FOUND_LOCAL_GLM 0 PARENT_SCOPE)
endif()

file(GLOB test-stbdir stb/stb*)
if (test-stbdir)
    SET(FOUND_LOCAL_STB 1 PARENT_SCOPE)
    add_library(stb INTERFACE)
    target_include_directories(stb INTERFACE stb/)
    add_library(stb::stb ALIAS stb)

    message(STATUS "[tewi] Found local stb in external/stb")
else()
    SET(FOUND_LOCAL_STB 0 PARENT_SCOPE)
endif()

file(GLOB test-asldir asl/CMakeLists.txt)
if (test-asldir)
    SET(FOUND_LOCAL_ASL 1 PARENT_SCOPE)
    add_subdirectory(asl)
    add_library(asl::asl ALIAS asl)

    message(STATUS "[tewi] Found local asl in external/asl")
else()
    SET(FOUND_LOCAL_ASL 0 PARENT_SCOPE)
endif()
