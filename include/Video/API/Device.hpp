#pragma once

#include "Video/API/Context.hpp"
#include "Video/API/Instance.hpp"

namespace tewi
{
	namespace API
	{
		template <unsigned int APINum>
		class Device
		{
		public:
			Device()
			{
				static_assert(isAPIValid(APINum), "Invalid API number for the device");
			}

			void init(Instance<APINum> instance) { }
			void cleanup() { }
		};
	}
}
