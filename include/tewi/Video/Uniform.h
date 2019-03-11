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
    /* TEWI_EXPORT */ void setUniform(asl::i32, T)
    {
        static_assert(detail::disable_type<T>::value, "Tried to pass an unsupported value");
    }

    template<>
    /* TEWI_EXPORT */ void setUniform<asl::f32>(asl::i32 uniformID, asl::f32 uniformVal)
    {
        glUniform1f(uniformID, uniformVal);
    }

    template<>
    /* TEWI_EXPORT */ void setUniform<asl::f64>(asl::i32 uniformID, asl::f64 uniformVal)
    {
        glUniform1d(uniformID, uniformVal);
    }

    template<>
    /* TEWI_EXPORT */ void setUniform<asl::u32>(asl::i32 uniformID, asl::u32 uniformVal)
    {
        glUniform1ui(uniformID, uniformVal);
    }

    template<>
    /* TEWI_EXPORT */ void setUniform<asl::i32>(asl::i32 uniformID, asl::i32 uniformVal)
    {
        glUniform1i(uniformID, uniformVal);
    }

    /* TEWI_EXPORT */ void setUniform(asl::i32 uniformID, const glm::mat4& matrix)
    {
        glUniformMatrix4fv(uniformID, 1, GL_FALSE, &matrix[0][0]);
    }

    /* TEWI_EXPORT */ void setUniform(asl::i32 uniformID, const std::vector<asl::num>& vec)
    {
        glUniform1iv(uniformID, vec.size(), vec.data());
    }

    template <const asl::sizei N> 
    /* TEWI_EXPORT */ void setUniform(asl::i32 uniformID, const std::array<asl::num, N>& arr)
    {
        glUniform1iv(uniformID, arr.size(), arr.data());
    }
}



#endif /* UNIFORM_HELPERS_H */
