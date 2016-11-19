#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#include <string>
#include "Platform/OpenGL/GLContext.h"
#include "Platform/Vulkan/VkContext.h"
#include "Log.h"
#include "Utils/DebugOnly.h"
#include "Utils/GLFWCallbacks.h"

namespace tewi
{
	template <unsigned int APINum>
	class Window
	{
	public:
		Window(const std::string& windowName, int width, int height)
			: m_width(width), m_height(height), m_windowName(windowName)
		{
			glfwInit();

			m_context.setup();
			

			glfwSwapInterval(0);

			m_window = glfwCreateWindow(m_width, m_height, windowName.c_str(), nullptr, nullptr);
			Ensures(m_window != nullptr, "Window not initialized");

			glfwMakeContextCurrent(m_window);
			glfwSetWindowSizeCallback(m_window, windowResizeCallback);

			m_context.postInit();

			//DebugOnly<int> error = glewInit();
			//Ensures(error == GLEW_OK, "Failed GLEW initialization");

			//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

			//glEnable(GL_BLEND);
			//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			std::printf("API Version: %s\n", m_context.getAPIVersion());
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

		inline auto* getContext() { return &m_context; }
	private:
		GLFWwindow* m_window;
		int m_width;
		int m_height;
		std::string m_windowName;
		API::Context<APINum> m_context;
	};
}

#endif /* WINDOW_H */
