#pragma once


#include <GL/glew.h>

#include "GLFW/glfw3.h"

#include "Log.h"

#include "Common.h"

namespace tewi
{

    template <class Derived, typename APINum>
    class GameCommon;

    inline static TEWI_EXPORT void windowResizeCallback(GLFWwindow*, int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    inline static TEWI_EXPORT void glfwErrorCallback(int error, const char* description)
    {
        Log::error(std::to_string(error) + " " + description);
    }

    // Thanks GLFW
    template <class Derived, typename APINum>
    inline static void glfwKeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        auto* gc = static_cast<GameCommon<Derived, APINum>*>(glfwGetWindowUserPointer(window));

        if (action == GLFW_PRESS)
        {
            gc->m_inputManager.pressKey(key);
        }
        else if (action == GLFW_RELEASE)
        {
            gc->m_inputManager.releaseKey(key);
        }
    }

    template <class Derived, typename APINum>
    inline static void glfwMouseCallback(GLFWwindow* window, int button, int action, int mods)
    {
        auto* gc = static_cast<GameCommon<Derived, APINum>*>(glfwGetWindowUserPointer(window));

        if (action == GLFW_PRESS)
        {
            gc->m_inputManager.pressKey(button);
        }
        else if (action == GLFW_RELEASE)
        {
            gc->m_inputManager.releaseKey(button);
        }
    }

    template <class Derived, typename APINum>
    inline static TEWI_EXPORT void glfwCursorPosCallback(GLFWwindow* window, double, double)
    {
        auto* gc = static_cast<GameCommon<Derived, APINum>*>(glfwGetWindowUserPointer(window));

        double xpos = 0;
        double ypos = 0;
        glfwGetCursorPos(window, &xpos, &ypos);
        gc->m_inputManager.setMouseCoords(glm::vec2{xpos, ypos});
    }
}
