# System library
find_package(glfw3)

set(TEWI_GLFW_TARGET_NAME glfw)

if (NOT TARGET glfw)
    find_package(glfw REQUIRED)
    set(TEWI_GLFW_TARGET_NAME glfw::glfw)
endif()

find_package(glm REQUIRED)

set(TEWI_GLM_TARGET_NAME glm)

if (TARGET glm::glm)
    set(TEWI_GLM_TARGET_NAME glm::glm)
endif()

find_package(stb REQUIRED)

set(TEWI_STB_TARGET_NAME stb)

if (TARGET stb::stb)
    set(TEWI_STB_TARGET_NAME stb::stb)
endif()

find_package(asl REQUIRED)

set(TEWI_ASL_TARGET_NAME asl)

if (TARGET asl::asl)
    set(TEWI_ASL_TARGET_NAME asl::asl)
endif()

if (TEWI_ENABLE_VULKAN)
    message(STATUS "[tewi] Vulkan enabled")
    target_compile_definitions(${PROJECT_NAME}
        PUBLIC
        GLFW_INCLUDE_VULKAN
        TEWI_ENABLE_VULKAN)

    find_package(Vulkan REQUIRED)
    target_link_libraries(${PROJECT_NAME} PUBLIC Vulkan::Vulkan)
endif()

if(WIN32)
    set(WIN32_OPENGL_LIBS
        opengl32.lib)
endif()

add_library(tewi-stb STATIC
    src/Utils/stb.cpp)

target_link_libraries(tewi-stb
    PUBLIC
    ${TEWI_STB_TARGET_NAME})

target_link_libraries(${PROJECT_NAME}
    PUBLIC
    ${WIN32_OPENGL_LIBS}
    tewi-glloader
    ${TEWI_GLM_TARGET_NAME}
    ${TEWI_GLFW_TARGET_NAME}
    ${TEWI_ASL_TARGET_NAME}
    tewi-stb)

if (TARGET ImGui)
    target_link_libraries(${PROJECT_NAME}
        PUBLIC
        ImGui)
endif()
