#pragma once

#include <GL/glew.h>

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#include <utility>
#include <string>
#include "Platform/OpenGL/Context.hpp"
#include "Platform/Vulkan/Context.hpp"
#include "Log.h"
#include "Utils/GLFWCallbacks.h"

#include "Common.h"

namespace tewi
{
	/** \brief Basic windowing system
	 *
	 * This class is the main windowing system.
	 *
	 * Basically manages the creation and instance of a window.
	 * It registers GLFW's callbacks, etc...
	 *
	 * \a APINum is used to initialize the window with the choosen graphic API.
	 *
	 * \sa API::Context
	 *
	 * \code
	 * using namespace tewi;
	 * constexpr int api = API::API_TYPE::OPENGL;
	 * Window<api> window("Title for your window", 800, 600);
	 *
	 * \endcode
	 */
	template <typename APINum>
	class TEWI_EXPORT Window
	{
	public:
		Window(std::string windowName, int width, int height)
			: m_width(width), m_height(height), m_windowName(std::move(windowName))
		{
			glfwInit();

			m_context.setup();
			
			m_window = glfwCreateWindow(m_width, m_height, windowName.c_str(), nullptr, nullptr);
			TEWI_ENSURES(m_window != nullptr, "Window not initialized");

			glfwMakeContextCurrent(m_window);

			glfwSetWindowSizeCallback(m_window, windowResizeCallback);
			glfwSetErrorCallback(glfwErrorCallback);

			m_context.postInit(m_window);
			std::printf("API Version: %s\n", m_context.getAPIVersion());
		}

		~Window()
		{
			glfwDestroyWindow(m_window);
		}

		Window(const Window& rhs) = delete;
		Window& operator=(const Window& rhs) = delete;

		/** Is the window closed?
		 *
		 */
		bool isWindowClosed()
		{
			return glfwWindowShouldClose(m_window);
		}

		/** Swaps the window buffers
		 *
		 */
		inline void swap() noexcept { m_context.swap(m_window); }

		/** Returns the width ofthe window
		 *
		 */
		inline int getWidth() const noexcept { return m_width; }

		/** Returns the height of the window
		 *
		 */
		inline int getHeight() const noexcept { return m_height; }

		/** Returns a pointer to the current instance of GLFWwindow
		 *
		 */
		inline GLFWwindow* getWindow() const noexcept { return m_window; }

		/** Returns a pointer to the current context used to initialize the API
		 *
		 */
		inline auto* getContext() { return &m_context; }
	private:
		GLFWwindow* m_window;
		int m_width;
		int m_height;
		std::string m_windowName;
		API::Context<APINum> m_context;
	};
}


// well
#include "Platform/NullRenderer/Window.hpp"
