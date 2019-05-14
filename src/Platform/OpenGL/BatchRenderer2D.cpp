#include "tewi/Platform/OpenGL/BatchRenderer2D.hpp"

#include <array>
#include <cstddef>
#include <algorithm>

#include <glm/glm.hpp>

#include "tewi/Common.h"
#include "tewi/Video/Renderable2D.hpp"
#include "tewi/Utils/Log.h"

#include "asl/types"

namespace tewi
{
    BatchRenderer2D<tewi::API::OpenGLTag>::BatchRenderer2D()
        : m_indexCount(0)
    {
        initBuffers();
        bindAttribPointers();
        finalInit();
    }

    BatchRenderer2D<tewi::API::OpenGLTag>::~BatchRenderer2D()
    {
        glDeleteBuffers(1, &m_VBO);
    }

    void BatchRenderer2D<tewi::API::OpenGLTag>::begin()
    {
        glUniform1iv(1, g_texIndices.size(), g_texIndices.data());
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        m_buffer = reinterpret_cast<Vertex*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
    }

    void BatchRenderer2D<tewi::API::OpenGLTag>::end()
    {
        glUnmapBuffer(GL_ARRAY_BUFFER);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void BatchRenderer2D<tewi::API::OpenGLTag>::draw()
    {
        for (asl::sizei i = 0; i < m_textureSlots.size(); ++i)
        {
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, m_textureSlots[i]);
        }

        glBindVertexArray(m_VAO);
        m_IBO->bind();

        glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, 0);

        m_IBO->unbind();
        glBindVertexArray(0);

        m_indexCount = 0;
    }

    ShaderProgram<API::OpenGLTag> BatchRenderer2D<tewi::API::OpenGLTag>::createShaderProgram()
    {
        constexpr asl::string_view vertstr =
        R"(
        #version 410 core
        #extension GL_ARB_explicit_uniform_location : enable

        layout(location = 0) in vec2 vertexPosition;
        layout(location = 1) in vec2 vertexUV;
        layout(location = 2) in float vertexTID;
        layout(location = 3) in vec4 vertexColor;

        out vec2 fragmentPosition;
        out float fragmentTID;
        out vec4 fragmentColor;
        out vec2 fragmentUV;

        uniform mat4 MVP;

        void main() {
            //Set the x,y position on the screen
            gl_Position = (MVP * vec4(vertexPosition, 0.0, 1.0));

            fragmentPosition = vertexPosition;

            fragmentColor = vertexColor;

            fragmentUV = vec2(vertexUV.x, 1.0 - vertexUV.y);
            fragmentTID = vertexTID;
        })";

        constexpr asl::string_view fragstr =
        R"(
        #version 410 core
        #extension GL_ARB_explicit_uniform_location : enable

        in vec2 fragmentPosition;
        in vec2 fragmentUV;
        in float fragmentTID;
        in vec4 fragmentColor;

        out vec4 color;

        layout(location = 1) uniform sampler2D textures[16];

        void main() {
            int tid = int(fragmentTID - 0.5);
            vec4 textureColor = texture(textures[tid], fragmentUV);
            color = fragmentColor * textureColor;
        })";

        constexpr std::array<ShaderDescription, 2> shaders
        {
            ShaderDescription{ vertstr, ShaderType::Vertex },
            ShaderDescription{ fragstr, ShaderType::Fragment },
        };

        constexpr std::array<asl::string_view, 4> attribs
        {
            "vertexPosition",
            "vertexUV",
            "vertexTID",
            "vertexColor"
        };

        return ShaderProgram<API::OpenGLTag>({ shaders.data(), shaders.size() },
                                             { attribs.data(), attribs.size() });

    }

    void BatchRenderer2D<tewi::API::OpenGLTag>::initBuffers()
    {
        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);

        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, g_bufferSize, 0, GL_DYNAMIC_DRAW);
    }

    void BatchRenderer2D<tewi::API::OpenGLTag>::bindAttribPointers()
    {
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glEnableVertexAttribArray(3);

        // Position
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(tewi::Vertex), (const void*)(0));

        // UV
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(tewi::Vertex), (const void*)(offsetof(Vertex, uv)));

        // TID
        glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(tewi::Vertex), (const void*)(offsetof(Vertex, textureID)));

        // Color
        glVertexAttribPointer(3, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(tewi::Vertex), (const void*)(offsetof(Vertex, color)));
    }

    void tewi::BatchRenderer2D<tewi::API::OpenGLTag>::finalInit()
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        std::vector<GLuint> indices(g_indicesSize);
        for (asl::sizei i = 0, offset = 0; i < indices.size(); i += 6, offset += 4)
        {
            indices[  i  ] = offset + 0;
            indices[i + 1] = offset + 1;
            indices[i + 2] = offset + 2;

            indices[i + 3] = offset + 2;
            indices[i + 4] = offset + 3;
            indices[i + 5] = offset + 0;
        }

        m_IBO = std::make_unique<IndexBuffer<API::OpenGLTag>>(indices);

        glBindVertexArray(0);
    }
}


