#pragma once

namespace tewi
{
    template <typename APITag>
    class IndexBuffer
    {
    public:
        using interface_only = void;

        template <typename Container>
        IndexBuffer(const Container& buffer);

        ~IndexBuffer();

        void bind();

        void unbind();
    };
} // namespace tewi

#include <tewi/Platform/OpenGL/IndexBuffer.h>
