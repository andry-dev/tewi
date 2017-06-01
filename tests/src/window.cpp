#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "Video/Window.hpp"

TEST_CASE("Create a window (OpenGL)", "[Unit][OpenGL]")
{
	tewi::Window<tewi::API::OpenGLTag> win("Test", 800, 600);
	while (!win.isWindowClosed())
	{
		win.forceClose();
	}
}

TEST_CASE("Create a window (Vulkan)", "[Unit][Vulkan]")
{
	tewi::Window<tewi::API::VulkanTag> win("Test", 800, 600);
	while (!win.isWindowClosed())
	{
		win.forceClose();
	}
}

TEST_CASE("Create a window (Null)", "[Unit][NullRenderer]")
{
	tewi::Window<tewi::API::NullRendererTag> win("Test", 800, 600);
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
			std::printf("woah");
		}

		std::printf("key = %d", key);
	};

	tewi::Window<tewi::API::OpenGLTag> win("Test", 800, 600);
	glfwSetKeyCallback(win.getWindow(), keycallback);

	while (!win.isWindowClosed())
	{
		win.pollEvents();

		win.getContext()->preDraw();
		win.getContext()->postDraw();

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

	tewi::Window<tewi::API::VulkanTag> win("Test", 800, 600);
	glfwSetKeyCallback(win.getWindow(), keycallback);

	while (!win.isWindowClosed())
	{
		win.pollEvents();

		win.getContext()->preDraw();
		win.getContext()->postDraw();

		win.swap();
	}
}
