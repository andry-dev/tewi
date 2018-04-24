
#include "tewi/Video/Window.hpp"
#include "asl/meta"
#include "asl/testing"
#include <chrono>

namespace
{
	using namespace std::literals::chrono_literals;
	const auto g_windowCloseTimeout = 2s;
}


template <typename Tag>
void win_creation()
{
    std::printf("\tWindow creation \n");
	tewi::Window<Tag> win("Test", 800, 600, nullptr);
	while (!win.isWindowClosed())
	{
		win.forceClose();
	}
    std::printf("\tPASSED\n");
}


template <typename Tag>
void poll_events()
{
    std::printf("\tPoll events \n");

	tewi::Window<Tag> win("Test", 800, 600, nullptr);
	win.setKeyboardCallback([](GLFWwindow* window, int key, int scancode, int action, int mods) {
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		{
			glfwWindowShouldClose(window);
		}
    });

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
    std::printf("\tPASSED\n");
}

void opengl()
{
    std::printf("[Window] OpenGL tests...\n");
    { win_creation<tewi::API::OpenGLTag>(); }
    { poll_events<tewi::API::OpenGLTag>(); }
}

void nullrend()
{
    std::printf("[Window] Null API tests...\n");
    win_creation<tewi::API::NullRendererTag>();
    poll_events<tewi::API::NullRendererTag>();
}

int main()
{
    opengl();
    nullrend();
}
