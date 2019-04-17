#pragma once

#include <array>
#include <string>

#include "tewi/Common.h"
#include "asl/types"
#include "gsl/string_span"
#include "gsl/span"

#include "tewi/IO/BasicIO.h"

#include "tewi/Video/API/Device.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace tewi
{
    enum class ShaderType : asl::i8
    {
        Vertex,
        Fragment,
        Geometry,
        Compute
    };

    struct ShaderDescription
    {
        asl::string_view sourceCode;
        ShaderType type;
    };

    struct VertexLayout
    {
        enum class Types : asl::i8
        {
            Float32, Float64,
            UInt8, Int8,
            UInt16, Int16,
            UInt32, Int32
        };

        asl::i8 index;
        Types type;
        asl::i8 count;
        bool normalized = false;
        asl::i16 stride;
        asl::i16 offset;
    };

    template <typename APITag>
    class ShaderProgram
    {
    public:
        using interface_only = void;

        ShaderProgram(gsl::span<const ShaderDescription> descriptions,
                      gsl::span<const asl::string_view> attributes);

        ~ShaderProgram();

        void enable();
        void disable();
        asl::i32 getUniformLocation(asl::string_view str);
        void setUniform(asl::i32 uniform, const glm::mat4& mat);
    };

    template <typename APITag>
    auto translateVertexLayoutType(APITag tag, VertexLayout::Types type);


    /** \example shader_creation.cpp
     *
     * Shows how to create a shader program.
     */
}

//#include "tewi/Platform/Vulkan/Shader.hpp"
//#include "tewi/Platform/NullRenderer/Shader.hpp"
#include <tewi/Platform/OpenGL/Shader.hpp>
