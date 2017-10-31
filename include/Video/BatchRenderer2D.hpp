#pragma once

#include "Video/Renderer2D.hpp"
#include "Video/Shader.hpp"
#include <array>
#include <vector>

#include "Common.h"

namespace tewi
{

    template <typename APIType>
    struct TEWI_EXPORT BatchRenderer2D
    {
    public:
        using interface_only = void;
    protected:
        BatchRenderer2D() = default;
        BatchRenderer2D(const BatchRenderer2D& rhs) = delete;
        BatchRenderer2D& operator=(const BatchRenderer2D& rhs) = delete;

        BatchRenderer2D(BatchRenderer2D&& rhs) = default;
        BatchRenderer2D& operator=(BatchRenderer2D&& rhs) = default;

        void begin();

        template <typename T>
        void add(const Renderable2D<T>& renderable);

        template <typename Container>
        void add(const Container& renderableList);

        void end();

        void draw();

        static ShaderProgram<APIType> createShaderProgram();
    };
} // namespace tewi

#include "Platform/OpenGL/BatchRenderer2D.hpp"
#include "Platform/NullRenderer/BatchRenderer2D.hpp"
