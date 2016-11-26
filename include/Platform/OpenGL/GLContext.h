#ifndef TEWI_OPENGL_CONTEXT_H
#define TEWI_OPENGL_CONTEXT_H

#include <GL/glew.h>
#include "GLFW/glfw3.h"

#include "Video/API/Context.h"

#include "Log.h"
#include "Utils/DebugOnly.h"

namespace tewi
{
	namespace API
	{
		/** \brief OpenGL Context.
		 *
		 *
		 * Initializes OpenGL.
		 *
		 * **Internal use only.**
		 */
		template<>
		class Context<API_TYPE::OPENGL>
		{
		public:
			Context()
			{

			}

			void setup()
			{
				// FUCKING MESA
				// THIS IS UNDER AMDGPU AND MESA-GIT, I DUNNO IF IT WORKS ON INTEL
				glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
				glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
				glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
				glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

			}

			void postInit()
			{
				DebugOnly<int> error = glewInit();
				Ensures(error == GLEW_OK, "Failed GLEW initialization");

				glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

				glEnable(GL_BLEND);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			}

			void preDraw()
			{
				glClearDepth(1.0f);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			}

			void postDraw()
			{

			}

			const unsigned char* getAPIVersion()
			{
				return glGetString(GL_VERSION);
			}
		};

		using GLContext = Context<API_TYPE::OPENGL>;
	}
}


#endif /* TEWI_OPENGL_CONTEXT_H */
