#ifndef TEWI_VULKAN_CONTEXT_H
#define TEWI_VULKAN_CONTEXT_H

#include "Video/API/Context.h"

namespace tewi
{
	namespace Video
	{
		namespace API
		{
			template<>
			class Context<API_TYPE::VULKAN>
			{
			public:
				Context()
				{

				}
			};

			using VkContext = Context<API_TYPE::VULKAN>;
		}
	}
}

#endif /* TEWI_VULKAN_CONTEXT_H */
