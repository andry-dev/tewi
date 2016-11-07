#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#include <string>
#include "Video/API/Context.h"
#include "Log.h"
#include "Utils/DebugOnly.h"
#include "Utils/GLFWCallbacks.h"

namespace tewi
{
	namespace Video
	{
		template <unsigned int APINum>
		class Window
		{
		public:
			Window(const std::string& windowName, int width, int height)
				: m_width(width), m_height(height), m_windowName(windowName)
			{
				glfwInit();

				// FUCKING MESA
				// THIS IS UNDER AMDGPU AND MESA-GIT, I DUNNO IF IT WORKS ON INTEL
				glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
				glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
				glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
				glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
				glfwSwapInterval(0);

				m_window = glfwCreateWindow(m_width, m_height, windowName.c_str(), nullptr, nullptr);
				Ensures(m_window != nullptr, "Window not initialized");

				glfwMakeContextCurrent(m_window);
				glfwSetWindowSizeCallback(m_window, windowResizeCallback);

				DebugOnly<int> error = glewInit();
				Ensures(error == GLEW_OK, "Failed GLEW initialization");

				glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

				std::printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
			}

			~Window()
			{
				glfwDestroyWindow(m_window);
			}

			Window(const Window& rhs) = delete;
			Window& operator=(const Window& rhs) = delete;

			Window(Window&& rhs)
				: m_window(rhs.m_window), m_width(std::move(rhs.m_width)),
				m_height(std::move(rhs.m_height)), m_windowName(std::move(rhs.m_windowName))
			{
				rhs.m_window = nullptr;
			}

			Window& operator=(Window&& rhs)
			{	
				if (this != &rhs)
				{
					glfwDestroyWindow(m_window);
					m_window = rhs.m_window;
					rhs.m_window = nullptr;

					m_width = std::move(rhs.m_width);
					m_height = std::move(rhs.m_height);
					m_windowName = std::move(rhs.m_windowName);
				}
				return *this;
			}

			bool isWindowClosed()
			{
				return glfwWindowShouldClose(m_window);
			}

			inline void swap() const noexcept { glfwSwapBuffers(m_window); }

			inline int getWidth() const noexcept { return m_width; }
			inline int getHeight() const noexcept { return m_height; }

			inline GLFWwindow* getWindow() const noexcept { return m_window; }
		private:
			GLFWwindow* m_window;
			int m_width;
			int m_height;
			std::string m_windowName;
			API::Context<APINum> m_context;
		};

	}
}

#endif /* WINDOW_H */
