#pragma once

#include "API/API.h"
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
		Window(std::string windowName, int width, int height)
			: m_windowName(windowName)
			, m_width(width)
			, m_height(height)
		{
		}

		~Window() = default;
		Window(const Window& rhs) = delete;
		Window& operator=(const Window& rhs) = delete;

		Window(Window&& rhs) = default;
		Window& operator=(Window&& rhs) = default;

		inline bool isWindowClosed() { return false; }

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
	};
} // namespace tewi
