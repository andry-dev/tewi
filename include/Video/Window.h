#ifndef WINDOW_H
#define WINDOW_H


#include <GL/glew.h>

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#include <string>

namespace tewi
{
	namespace Video
	{
		class Window
		{
		public:
			Window(const std::string& windowName, int width, int height);
			~Window();

			Window(const Window& rhs) = delete;
			Window& operator=(const Window& rhs) = delete;

			Window(Window&& rhs);
			Window& operator=(Window&& rhs);

			bool isWindowClosed();

			inline void swap() const noexcept { glfwSwapBuffers(m_window); }

			inline int getWidth() const noexcept { return m_width; }
			inline int getHeight() const noexcept { return m_height; }

			inline GLFWwindow* getWindow() const noexcept { return m_window; }
		private:
			GLFWwindow* m_window;
			int m_width;
			int m_height;
			std::string m_windowName;
		};
	}
}

#endif /* WINDOW_H */
