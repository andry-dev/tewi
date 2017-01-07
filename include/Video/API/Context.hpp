#pragma once

#include "Video/API/API.h"

#include <GL/glew.h>

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

namespace tewi
{
	/** Common namespace for Graphic API related stuff like context, renderers, etc...
	 *
	 *
	 */
	namespace API
	{
		/** \brief Context initialization
		 * Initializes graphic API for the window.
		 *
		 * Requires \a APINum that should be a value from the enum **API::API_TYPE**.
		 *
		 * You should *not* instantiate this class without a valid API, only the Window uses this.
		 *
		 * 
		 * \sa Context<API_TYPE::OPENGL>
		 * \sa Context<API_TYPE::VULKAN>
		 * \sa Window
		 */
		template <unsigned int APINum>
		class Context
		{
		public:
			Context()
			{
				static_assert(isAPIValid(APINum), "Invalid API number for the context");
			}

			/** Steps before the window is initialized
			 *
			 */
			void setup() {  }

			/** Steps after the window is initialized
			 *
			 */
			void postInit(GLFWwindow*) {  }

			/** Steps before drawing
			 *
			 */
			void preDraw() {  }
			
			/** Steps after drawing
			 *
			 */
			void postDraw() {  }

			/** Buffer Swap
			 *
			 */
			void swap(GLFWwindow*) {  }

			/** Returns API information
			 *
			 */
			const auto getAPIVersion() { return "UNKOWN_CONTEXT"; }
		};

	}
}
