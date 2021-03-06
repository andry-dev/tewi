#pragma once

#include <tewi/Video/IndexBuffer.hpp>
#include <tewi/Video/API/API.h>
#include <tewi/Platform/OpenGL/Glew.h>

namespace tewi
{
    template <>
    class IndexBuffer<API::OpenGLTag>
    {
    public:
        template <typename Container>
        IndexBuffer(const Container& buffer);

        ~IndexBuffer();

        void bind();

        void unbind();
    private:
        GLuint m_bufferID;
    };

    template <typename Container>
    IndexBuffer<tewi::API::OpenGLTag>::IndexBuffer(const Container& buffer)
    {
        glGenBuffers(1, &m_bufferID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, buffer.size() * sizeof(typename Container::value_type), buffer.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}
