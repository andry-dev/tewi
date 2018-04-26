
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
	tewi::Window<Tag> win("Test", tewi::Width{800}, tewi::Height{600}, nullptr);
	while (!tewi::isWindowClosed(win))
	{
        tewi::forceCloseWindow(win);
	}
    std::printf("\tPASSED\n");
}


template <typename Tag>
void poll_events()
{
    std::printf("\tPoll events \n");

	tewi::Window<Tag> win("Test", tewi::Width{800}, tewi::Height{600}, nullptr);
    tewi::setWindowKeyboardCallback(win,
                                    [](GLFWwindow* window, int key,
                                       int scancode, int action, int mods)
    {
		if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		{
			glfwWindowShouldClose(window);
		}
    });

	const auto start = std::chrono::system_clock::now();

	while (!tewi::isWindowClosed(win))
	{
		const auto now = std::chrono::system_clock::now();

		if (now - start >= g_windowCloseTimeout)
		{
            tewi::forceCloseWindow(win);
		}

        tewi::pollWindowEvents(win);

		win.context.preDraw();
		win.context.postDraw();

        tewi::swapWindowBuffers(win);
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
