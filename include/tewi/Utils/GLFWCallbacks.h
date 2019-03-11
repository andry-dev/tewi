#pragma once


#include <GL/glew.h>

#include "GLFW/glfw3.h"

#include "Log.h"

#include "tewi/Common.h"

#include "glm/glm.hpp"

namespace tewi
{

    inline static TEWI_EXPORT void windowResizeCallback(GLFWwindow*, int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    inline static TEWI_EXPORT void glfwErrorCallback(int error, const char* description)
    {
        Log::error(std::to_string(error) + " " + description);
    }

}
