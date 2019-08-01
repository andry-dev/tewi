set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_BINARY_DIR})

if (NOT FOUND_LOCAL_GLFW)
    find_package(glfw REQUIRED)
endif()

if (NOT FOUND_LOCAL_GLM)
    find_package(glm REQUIRED)
endif()

if (NOT FOUND_LOCAL_STB)
    find_package(stb REQUIRED)
endif()

if (NOT FOUND_LOCAL_ASL)
    find_package(asl REQUIRED)
endif()
