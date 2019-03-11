#include <GL/glew.h>

#include "tewi/Video/API/API.h"
#include "tewi/Video/IndexBuffer.hpp"

namespace tewi
{
    template <>
    class IndexBuffer<API::OpenGLTag>
    {
    public:
        template <typename Container>
        IndexBuffer(const Container& buffer)
        {
            glGenBuffers(1, &m_bufferID);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, buffer.size() * sizeof(typename Container::value_type), buffer.data(), GL_STATIC_DRAW);
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
