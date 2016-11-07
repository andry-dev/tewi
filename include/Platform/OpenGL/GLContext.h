#ifndef TEWI_OPENGL_CONTEXT_H
#define TEWI_OPENGL_CONTEXT_H

#include "Video/API/Context.h"

namespace tewi
{
	namespace Video
	{
		namespace API
		{
			template<>
			class Context<API_TYPE::OPENGL>
			{
			public:
				Context()
				{

				}
			};

			using GLContext = Context<API_TYPE::OPENGL>;
		}
	}
}


#endif /* TEWI_OPENGL_CONTEXT_H */
