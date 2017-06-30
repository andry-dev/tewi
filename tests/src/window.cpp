#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "Video/Window.hpp"
#include <chrono>

namespace
{
	using namespace std::literals::chrono_literals;
	const auto g_windowCloseTimeout = 2s;
}

TEST_CASE("Create a window (OpenGL)", "[Unit][OpenGL]")
{
	tewi::Window<tewi::API::OpenGLTag> win("Test", 800, 600, nullptr);
	while (!win.isWindowClosed())
	{
		win.forceClose();
	}
}

TEST_CASE("Create a window (Vulkan)", "[Unit][Vulkan]")
{
	tewi::Window<tewi::API::VulkanTag> win("Test", 800, 600, nullptr);
	while (!win.isWindowClosed())
	{
		win.forceClose();
	}
}

TEST_CASE("Create a window (Null)", "[Unit][NullRenderer]")
{
	tewi::Window<tewi::API::NullRendererTag> win("Test", 800, 600, nullptr);
	while (!win.isWindowClosed())
	{
		win.forceClose();
	}
}

TEST_CASE("Poll events (OpenGL)", "[Unit][OpenGL]")
{
	auto keycallback = [] (GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		{
			glfwWindowShouldClose(window);
		}
	};

	tewi::Window<tewi::API::OpenGLTag> win("Test", 800, 600, nullptr);
	glfwSetKeyCallback(win.getWindow(), keycallback);

	const auto start = std::chrono::system_clock::now();

	while (!win.isWindowClosed())
	{
		const auto now = std::chrono::system_clock::now();

		if (now - start >= g_windowCloseTimeout)
		{
			win.forceClose();
		}

		win.pollEvents();

		win.getContext().preDraw();
		win.getContext().postDraw();

		win.swap();
	}
}

TEST_CASE("Poll events (Vulkan)", "[Unit][Vulkan]")
{
	auto keycallback = [] (GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		{
			glfwWindowShouldClose(window);
		}
		
		std::printf("key = %d", key);
	};

	tewi::Window<tewi::API::VulkanTag> win("Test", 800, 600, nullptr);
	glfwSetKeyCallback(win.getWindow(), keycallback);

	const auto start = std::chrono::system_clock::now();

	while (!win.isWindowClosed())
	{
		const auto now = std::chrono::system_clock::now();

		if (now - start >= g_windowCloseTimeout)
		{
			win.forceClose();
		}

		win.pollEvents();

		win.getContext().preDraw();
		win.getContext().postDraw();

		win.swap();
	}
}
