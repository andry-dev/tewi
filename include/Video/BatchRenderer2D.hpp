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

		/** Begins the rendering by binding the buffers.
		 *
		 * That's the first function you need to call.
		 *
		 */
		void begin()
		{
		}

		/** Add a **single** renderables to the buffer.
		 *
		 * Call this function one or multiple time **after** \a begin() and **before** \a end().
		 * 
		 * Example:
		 *
		 * \code
		 * // Assuming a BatchRenderer named "batch"
		 * // Also assuming a Sprite named "spr"
		 *
		 * batch.add(spr.getRenderable());
		 *
		 * // Or, if the Sprite supports implicit conversion to a Renderable2D
		 *
		 * batch.add(spr);
		 *
		 * \endcode
		 */
		void add(const Renderable2D& renderable)
		{
		}

		/** Add a **vector** of renderables to the buffer.
		 *
		 * Call this function one or multiple time **after** \a begin() and **before** \a end().
		 * 
		 * Example:
		 *
		 * \code
		 * 
		 * // Assuming a BatchRenderer named "batch"
		 * // And assuming a std::vector of Renderable2Ds named "vec"
		 *
		 * batch.add(vec);
		 *
		 * \endcode
		 *
		 */
		void add(const std::vector<Renderable2D>& renderableList)
		{
		}

		/** Unbinds the buffers.
		 *
		 * Call this after adding the renderables with \a add() and before \a draw().
		 *
		 */
		void end()
		{
		}

		/** Does the draw call and resets the buffer.
		 *
		 * You need to do this **after** \a end().
		 *
		 * This is the last function you need to call.
		 *
		 */
		void draw()
		{
		}
	};
} // namespace tewi
