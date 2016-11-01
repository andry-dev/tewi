#ifndef TEWI_OPENGL_CONTEXT_H
#define TEWI_OPENGL_CONTEXT_H

#include "Video/API/Context.h"

namespace tewi
{
	namespace Platform
	{
		namespace API
		{
			class GLContext : public Video::API::ContextCreation
			{
			public:
				GLContext(const Video::API::WindowProps& window);

				
			private:
				Video::API::WindowProps m_props;
			};
		}
	}
}


#endif /* TEWI_OPENGL_CONTEXT_H */
