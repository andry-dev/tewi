#pragma once

#include "Video/Renderer2D.hpp"
#include <array>
#include <vector>

namespace tewi
{
	template <typename APIType>
	struct BatchRenderer2D
	{
	protected:
		BatchRenderer2D(const BatchRenderer2D& rhs) = delete;
		BatchRenderer2D& operator=(const BatchRenderer2D& rhs) = delete;

		BatchRenderer2D(BatchRenderer2D&& rhs) = default;
		BatchRenderer2D& operator=(BatchRenderer2D&& rhs) = default;

		void begin()
		{
		}

		void add(const Renderable2D& renderable)
		{
		}

		void add(const std::vector<Renderable2D>& renderableList)
		{
		}

		void end()
		{
		}

		void draw()
		{
		}
	};
} // namespace tewi

#include "Platform/OpenGL/BatchRenderer2D.hpp"
