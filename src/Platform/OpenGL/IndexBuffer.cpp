#include "tewi/Video/IndexBuffer.hpp"

namespace tewi
{

    IndexBuffer<tewi::API::OpenGLTag>::~IndexBuffer()
    {
        glDeleteBuffers(1, &m_bufferID);
    }

    void IndexBuffer<tewi::API::OpenGLTag>::bind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID);
    }

    void IndexBuffer<tewi::API::OpenGLTag>::unbind()
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}
