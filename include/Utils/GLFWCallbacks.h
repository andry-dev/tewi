#ifndef TEWI_GLFW_CALLBACKS_H
#define TEWI_GLFW_CALLBACKS_H

#include <GL/glew.h>

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

namespace tewi
{

	inline void windowResizeCallback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

}

#endif /* TEWI_GLFW_CALLBACKS_H */
