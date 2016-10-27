#include "Video/Window.h"

#include "Log.h"
#include "Utils/DebugOnly.h"

namespace tewi
{
	namespace Video
	{

		void windowResizeCallback(GLFWwindow* window, int width, int height);


		Window::Window(const std::string& windowName, int width, int height)
			: m_width(width), m_height(height), m_windowName(windowName)
		{

			glfwInit();

			// FUCKING MESA
			// THIS IS UNDER AMDGPU AND MESA-GIT, I DUNNO IF IT WORKS ON INTEL
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  // yes, 3 and 2!!!
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

			std::printf(" OpenGL Version: %s\n", glGetString(GL_VERSION));
		}

		Window::~Window()
		{
			glfwDestroyWindow(m_window);
		}

		Window::Window(Window&& rhs)
			: m_window(rhs.m_window), m_width(std::move(rhs.m_width)),
			m_height(std::move(rhs.m_height)), m_windowName(std::move(rhs.m_windowName))
		{
			rhs.m_window = nullptr;
		}

		Window& Window::operator=(Window&& rhs)
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

		/// I wouldn't use this
		bool Window::isWindowClosed()
		{
			return glfwWindowShouldClose(m_window);
		}
	
		void windowResizeCallback(GLFWwindow* window, int width, int height)
		{
			glViewport(0, 0, width, height);
		}
	}
}
