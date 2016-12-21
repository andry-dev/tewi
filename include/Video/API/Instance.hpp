#pragma once

#include "Video/API/Context.hpp"

namespace tewi
{
	namespace API
	{
		template <unsigned int APINum>
		class Instance
		{
		public:
			Instance()
			{
				static_assert(isAPIValid(APINum), "Invalid API number for the instance");
			}

			~Instance() { }

			void init() { } 
			void cleanup() {  }
		};
	}
}
