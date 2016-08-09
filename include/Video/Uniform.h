#ifndef UNIFORM_HELPERS_H
#define UNIFORM_HELPERS_H

#include <cstdint>
#include <GL/glew.h>

#include <type_traits>

namespace tewi
{
	namespace Video
	{
		namespace detail
		{
			template <typename T>
			struct disable_type : std::false_type
			{  };
		}

		template<typename T>
		void setUniform(std::int32_t, T)
		{
			static_assert(detail::disable_type<T>::value, "Tried to pass an unsupported value");
		}

		template<>
		void setUniform<float>(std::int32_t uniformID, float uniformVal)
		{
			glUniform1f(uniformID, uniformVal);
		}

		template<>
		void setUniform<double>(std::int32_t uniformID, double uniformVal)
		{
			glUniform1d(uniformID, uniformVal);
		}

		template<>
		void setUniform<std::uint32_t>(std::int32_t uniformID, std::uint32_t uniformVal)
		{
			glUniform1ui(uniformID, uniformVal);
		}

		template<>
		void setUniform<std::int32_t>(std::int32_t uniformID, std::int32_t uniformVal)
		{
			glUniform1i(uniformID, uniformVal);
		}
	}
}



#endif /* UNIFORM_HELPERS_H */
