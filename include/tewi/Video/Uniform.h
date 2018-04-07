#ifndef UNIFORM_HELPERS_H
#define UNIFORM_HELPERS_H

#include <cstdint>
#include <type_traits>
#include <vector>
#include <GL/glew.h>

#include "glm/glm.hpp"

#include "tewi/Common.h"
#include "tewi/Utils/Log.h"

namespace tewi
{
    namespace detail
    {
        template <typename T>
        struct disable_type : std::false_type
        {  };
    }

    template<typename T>
    /* TEWI_EXPORT */ void setUniform(std::int32_t, T)
    {
        static_assert(detail::disable_type<T>::value, "Tried to pass an unsupported value");
    }

    template<>
    /* TEWI_EXPORT */ void setUniform<float>(std::int32_t uniformID, float uniformVal)
    {
        glUniform1f(uniformID, uniformVal);
    }

    template<>
    /* TEWI_EXPORT */ void setUniform<double>(std::int32_t uniformID, double uniformVal)
    {
        glUniform1d(uniformID, uniformVal);
    }

    template<>
    /* TEWI_EXPORT */ void setUniform<std::uint32_t>(std::int32_t uniformID, std::uint32_t uniformVal)
    {
        glUniform1ui(uniformID, uniformVal);
    }

    template<>
    /* TEWI_EXPORT */ void setUniform<std::int32_t>(std::int32_t uniformID, std::int32_t uniformVal)
    {
        glUniform1i(uniformID, uniformVal);
    }

    /* TEWI_EXPORT */ void setUniform(std::int32_t uniformID, const glm::mat4& matrix)
    {
        glUniformMatrix4fv(uniformID, 1, GL_FALSE, &matrix[0][0]);
    }

    /* TEWI_EXPORT */ void setUniform(std::int32_t uniformID, const std::vector<int>& vec)
    {
        glUniform1iv(uniformID, vec.size(), vec.data());
    }

    template <asl::sizei N> 
    /* TEWI_EXPORT */ void setUniform(std::int32_t uniformID, const std::array<int, N>& arr)
    {
        glUniform1iv(uniformID, arr.size(), arr.data());
    }
}



#endif /* UNIFORM_HELPERS_H */
