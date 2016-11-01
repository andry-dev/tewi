#ifndef TEWI_API_CONTEXT_H
#define TEWI_API_CONTEXT_H

#include "Utils/String.hpp"

// #include "Platform/OpenGL/VKContext.h"
#include "Platform/OpenGL/GLContext.h"

namespace tewi
{
	namespace Video
	{
		namespace API
		{
			enum class API_TYPE
			{
				NULL_RENDERER,
				OPENGL,
				VULKAN
			};

			class ContextCreation
			{
				public:
					virtual void setHints() = 0;
					virtual void create() = 0;
			};
		}
	}
}

#endif /* TEWI_API_CONTEXT_H */
