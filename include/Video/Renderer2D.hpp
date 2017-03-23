#pragma once

#include "Video/API/API.h"
#include "Video/Renderable2D.hpp"
#include <vector>

#include "Log.h"

namespace tewi
{
	template <typename APIType,
			 template <typename> class RenderPolicy>
	class Renderer2D
		: public RenderPolicy<APIType>
	{
		using RenderPolicyImpl = RenderPolicy<APIType>;
	public:
		Renderer2D()
		{
			Log::debugInfo("Renderer2D<>::Renderer2D");
		}

		~Renderer2D() = default;

		Renderer2D(const Renderer2D& rhs) = delete;
		Renderer2D& operator=(const Renderer2D& rhs) = default;

		Renderer2D(Renderer2D&& rhs) =  delete;
		Renderer2D& operator=(Renderer2D&& rhs) = default;

		void begin()
		{
			RenderPolicyImpl::begin();
		}

		void add(const std::vector<Renderable2D>& renderables)
		{
			RenderPolicyImpl::add(renderables);
		}

		void add(const Renderable2D& renderable)
		{
			RenderPolicyImpl::add(renderable);
		}
		
		void end()
		{
			RenderPolicyImpl::end();
		}

		void draw()
		{
			RenderPolicyImpl::draw();
		}

	private:
	};
} // namespace tewi
