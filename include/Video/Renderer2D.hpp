#pragma once

#include "Video/API/API.h"
#include "Video/Renderable2D.hpp"
#include <vector>

#include "Log.h"

namespace tewi
{
	/** \brief A generic 2D renderer.
	 *
	 * A policy-based class that allows us to render stuff to the screen.
	 *
	 * \tparam APIType The API you want to use.
	 * \tparam RenderPolicy The policy that you want to use to render to the
	 * screen.
	 *
	 * \warning API **and** ABI instability: Inferface may change once Vulkan
	 * support is stable enough.
	 */
	template <typename APIType,
			 template <typename> class RenderPolicy>
	class Renderer2D final
		: public RenderPolicy<APIType>
	{
		using RenderPolicyImpl = RenderPolicy<APIType>;
	public:
		Renderer2D() {  }

		~Renderer2D() = default;

		Renderer2D(const Renderer2D& rhs) = delete;
		Renderer2D& operator=(const Renderer2D& rhs) = default;

		Renderer2D(Renderer2D&& rhs) =  delete;
		Renderer2D& operator=(Renderer2D&& rhs) = default;

		/** Begins the rendering by binding the buffers.
		 *
		 * That's the first function you need to call.
		 *
		 */
		void begin()
		{
			RenderPolicyImpl::begin();
		}

		/** Add a **vector** of renderables to the buffer.
		 *
		 * Example:
		 *
		 * \code
		 *
		 * // Assuming a Renderer named "renderer"
		 * // And assuming a std::vector of Renderable2Ds named "vec"
		 *
		 * renderer.add(vec);
		 *
		 * \endcode
		 *
		 * \pre You must call this function after \a begin() and before \a end().
		 */
		void add(const std::vector<Renderable2D<APIType>>& renderables)
		{
			RenderPolicyImpl::add(renderables);
		}

		/** Add a **single** renderables to the buffer.
		 * 
		 * Example:
		 *
		 * \code
		 * // Assuming a Renderer named "renderer"
		 * // Also assuming a Sprite named "spr"
		 *
		 * renderer.add(spr.getRenderable());
		 *
		 * // Or, if the Sprite supports implicit conversion to a Renderable2D
		 *
		 * renderer.add(spr);
		 *
		 * \endcode
		 *
		 * \pre You must call this function after \a begin() and before \a end().
		 */
		void add(const Renderable2D<APIType>& renderable)
		{
			RenderPolicyImpl::add(renderable);
		}

		/** Unbinds the buffers.
		 *
		 * \pre Call this after adding the renderables with \a add() and before \a draw().
		 *
		 */
		void end()
		{
			RenderPolicyImpl::end();
		}

		/** Does the draw call and resets the buffer.
		 *
		 * This is the last function you need to call.
		 *
		 * \pre Call this **after** \a end().
		 *
		 */
		void draw()
		{
			RenderPolicyImpl::draw();
		}

	private:
	};

	/** \example renderer2D_usage.cpp
	 *
	 * Usage of Renderer2D
	 */

} // namespace tewi
