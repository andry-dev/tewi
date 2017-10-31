#pragma once

#include "Video/API/API.h"
#include "Video/IndexBuffer.hpp"

#include <GL/glew.h>

namespace tewi
{
    template <>
    class IndexBuffer<API::OpenGLTag>
    {
    public:
        template <typename T>
        IndexBuffer(const std::vector<T>& buffer)
        {
            glGenBuffers(1, &m_bufferID);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, buffer.size() * sizeof(T), buffer.data(), GL_STATIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }

        ~IndexBuffer()
        {
            glDeleteBuffers(1, &m_bufferID);
        }
        
        void bind()
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID);
        }

        void unbind()
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }
    private:
        GLuint m_bufferID;
    };
}
