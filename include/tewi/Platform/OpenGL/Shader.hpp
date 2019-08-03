#pragma once

#include <tewi/Video/Shader.hpp>

namespace tewi
{
    template <>
    class ShaderProgram<API::OpenGLTag>
    {
    public:
        ShaderProgram(gsl::span<const ShaderDescription> descriptions,
                      gsl::span<const asl::string_view> attributes);

        ~ShaderProgram();

        void enable();
        void disable();

        asl::i32 getUniformLocation(asl::string_view str);
        void setUniform(asl::i32 uniform, const glm::mat4& mat);

    private:
        asl::u32 m_id { 0 };
        asl::isize m_attributeNum { 0 };
    };
} // namespace tewi
