#ifndef TEWI_API_CONTEXT_H
#define TEWI_API_CONTEXT_H

#include "Utils/WriteOnce.h"

namespace tewi
{
	namespace Video
	{
		namespace API
		{
			enum API_TYPE
			{
				NULL_RENDERER,
				OPENGL,
				VULKAN,
				END
			};

			static WriteOnce<unsigned int> g_currentAPI;

			template <unsigned int APINum>
			class Context
			{
			public:
				Context()
				{
					static_assert(APINum >= API_TYPE::NULL_RENDERER && APINum < API_TYPE::END, "Invalid API number");
				}

				auto getAPI() const { return m_API; }

			protected:
				unsigned int m_API = APINum;
			};

		}
	}
}

#endif /* TEWI_API_CONTEXT_H */
