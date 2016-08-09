#include "Video/Window.h"

#include "Log.h"
#include "Utils/DebugOnly.h"

namespace tewi
{
	namespace Video
	{
		Window::Window(const std::string& windowName, int width, int height)
			: m_width(width), m_height(height), m_windowName(windowName)
		{
			SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

			SDL_Init(SDL_INIT_EVERYTHING);
			m_window = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_width, m_height, SDL_WINDOW_OPENGL);
			Ensures(m_window != nullptr, "Window not initialized");

			DebugOnly<SDL_GLContext> glContext = SDL_GL_CreateContext(m_window);
			Ensures(glContext != nullptr, "Context not initialized");

			DebugOnly<int> error = glewInit();
			Ensures(error == GLEW_OK, "Failed GLEW initialization");

			glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		}

		Window::~Window()
		{
			SDL_DestroyWindow(m_window);
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
				SDL_DestroyWindow(m_window);
				m_window = rhs.m_window;
				rhs.m_window = nullptr;

				m_width = std::move(rhs.m_width);
				m_height = std::move(rhs.m_height);
				m_windowName = std::move(rhs.m_windowName);
			}
			return *this;
		}

		bool Window::isWindowClosed()
		{
			SDL_Event evnt;
			while (SDL_PollEvent(&evnt))
			{
				if (evnt.type == SDL_QUIT)
				{
					return true;
				}
			}

			return false;
		}
	}
}
