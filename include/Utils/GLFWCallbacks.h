#ifndef TEWI_GLFW_CALLBACKS_H
#define TEWI_GLFW_CALLBACKS_H


#include <GL/glew.h>

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#include "Log.h"

namespace tewi
{

	inline void windowResizeCallback(GLFWwindow*, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	inline void glfwErrorCallback(int error, const char* description)
	{
		Log::error(std::to_string(error) + " " + description);
	}

}

#endif /* TEWI_GLFW_CALLBACKS_H */
