#pragma once

namespace tewi
{
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

		/** Function that checks if an API is in a valid range
		 *
		 */
		constexpr bool isAPIValid(int APINum)
		{
			return APINum >= API_TYPE::NULL_RENDERER && APINum != API_TYPE::END;
		}

	}
}
