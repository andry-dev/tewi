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

add_library(stb_impl STATIC
    src/Utils/stb.cpp)

target_link_libraries(stb_impl
    PUBLIC
    stb::stb)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
    ${WIN32_OPENGL_LIBS}
    tewi-glloader
    glm::glm
    glfw::glfw
    asl::asl
    stb_impl)

if (TARGET ImGui)
    target_link_libraries(${PROJECT_NAME}
        PUBLIC
        ImGui)
endif()
