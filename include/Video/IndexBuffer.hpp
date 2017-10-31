#pragma once

namespace tewi
{
    template <typename APITag>
    class IndexBuffer
    {
    public:
        using interface_only = void;

        template <typename T>
        IndexBuffer(const std::vector<T>& buffer);
        
        void bind();

        void unbind();
    };
} // namespace tewi

#include "Platform/OpenGL/IndexBuffer.hpp"
