#pragma once

#include "Video/API/API.h"
#include "Common.h"

#include "Video/Window.hpp"
#include "Video/API/Context.hpp"

#include <string>

namespace tewi
{
	template <>
	class TEWI_EXPORT Window<API::NullRendererTag>
	{
	public:
		Window(std::string windowName, int width, int height, void* usrptr)
			: m_windowName(windowName)
			, m_width(width)
			, m_height(height)
			, m_windowClosed(false)
		{
		}

		~Window() = default;
		Window(const Window& rhs) = delete;
		Window& operator=(const Window& rhs) = delete;

		Window(Window&& rhs) = default;
		Window& operator=(Window&& rhs) = default;

		bool isWindowClosed() { return m_windowClosed; }
		inline void forceClose() { m_windowClosed = true; }
		inline void pollEvents() { }

		inline void swap() noexcept { }
		inline int getWidth() const noexcept { return m_width; }
		inline int getHeight() const noexcept { return m_height; }
		inline GLFWwindow* getWindow() const noexcept { return nullptr; }
		
		inline auto getContext() { return &m_context; }

	private:
		std::string m_windowName;
		int m_width;
		int m_height;
		API::Context<API::NullRendererTag> m_context;
		bool m_windowClosed;
	};
} // namespace tewi
