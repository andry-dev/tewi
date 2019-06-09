#pragma once

#include "tewi/Common.h"
#include "tewi/Video/API/API.h"
#include "tewi/Video/Shader.hpp"

namespace tewi
{
    template <>
    class TEWI_EXPORT ShaderProgram<API::NullRendererTag>
    {
    public:
        ShaderProgram(gsl::span<const ShaderDescription>,
                      gsl::span<const asl::string_view>)
        {
        }

        ~ShaderProgram() = default;

        void enable() {}
        void disable() {}
    };

    inline auto TEWI_EXPORT translateVertexLayoutType(API::NullRendererTag,
                                                      VertexLayout::Types)
    {
        return 0;
    }
} // namespace tewi
