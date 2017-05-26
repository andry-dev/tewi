#pragma once


#include <GL/glew.h>

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#include "Log.h"

#include "Common.h"

namespace tewi
{

	inline TEWI_EXPORT void windowResizeCallback(GLFWwindow*, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	inline TEWI_EXPORT void glfwErrorCallback(int error, const char* description)
	{
		Log::error(std::to_string(error) + " " + description);
	}

}
