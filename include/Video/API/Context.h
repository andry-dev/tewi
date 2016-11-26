#ifndef TEWI_API_CONTEXT_H
#define TEWI_API_CONTEXT_H

namespace tewi
{

	/** Common namespace for Graphic API related stuff like context, renderers, etc...
	 *
	 *
	 */
	namespace API
	{
		/** Enum for the various APIs supported in the engine.
		 *
		 */
		enum API_TYPE
		{
			NULL_RENDERER,
			OPENGL,
			VULKAN,
			END
		};

		/** \brief Context initialization
		 * Initializes graphic API for the window.
		 *
		 * Requires \a APINum that should be a value from the enum **API::API_TYPE**.
		 *
		 * You should *not* instantiate this class, only the Window uses this.
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
				static_assert(APINum >= API_TYPE::NULL_RENDERER && APINum < API_TYPE::END, "Invalid API number");
			}

			/** Steps before the window is initialized
			 *
			 */
			void setup() {  }

			/** Steps after the window is initialized
			 *
			 */
			void postInit() {  }

			/** Steps before drawing
			 *
			 */
			void preDraw() {  }
			
			/** Steps after drawing
			 *
			 */
			void postDraw() {  }

			/** Returns API information
			 *
			 */
			const unsigned char* getAPIVersion() { return "UNKOWN_CONTEXT"; }
		};

	}
}

#endif /* TEWI_API_CONTEXT_H */
