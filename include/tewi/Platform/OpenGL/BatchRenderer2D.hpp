#pragma once

#include "tewi/Video/BatchRenderer2D.hpp"
#include <tewi/Video/API/API.h>

#include <tewi/Platform/OpenGL/GL.h>

#include <memory>

#include "tewi/Video/IndexBuffer.hpp"
#include "tewi/Video/Vertex.h"

namespace tewi
{
    template <>
    struct TEWI_EXPORT BatchRenderer2D<API::OpenGLTag>
    {
    protected:
        BatchRenderer2D();

        ~BatchRenderer2D();

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

        static ShaderProgram<API::OpenGLTag> createShaderProgram();

    private:
        void initBuffers();

        void bindAttribPointers();

        void finalInit();

        GLuint m_VBO;
        GLuint m_VAO;
        tewi::Vertex* m_buffer;
        std::vector<GLuint> m_textureSlots;
        std::unique_ptr<tewi::IndexBuffer<API::OpenGLTag>> m_IBO;
        asl::i64 m_indexCount;

        static constexpr asl::i64 g_maxTextures = 64000;
        static constexpr asl::i64 g_vertexSize = sizeof(Vertex);
        static constexpr asl::i64 g_spriteSize = g_vertexSize * 4;
        static constexpr asl::i64 g_bufferSize = g_spriteSize * g_maxTextures;
        static constexpr asl::i64 g_indicesSize = g_maxTextures * 6;

        inline static constexpr std::array<int, 16> g_texIndices = {
            0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15
        };
    };

    /*
    static constexpr std::array<int, 16>
    BatchRenderer2D<tewi::API::OpenGLTag>::g_texIndices =
    {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15
    };
    */

    template <typename T>
    void BatchRenderer2D<tewi::API::OpenGLTag>::add(
        const Renderable2D<T>& renderable)
    {
        const auto& size = renderable.texture.size;
        const auto tid = renderable.texture.id;
        const auto scale = renderable.scale;

        float ts = 0;

        if (tid > 0)
        {
            bool foundTextureID = false;
            for (asl::sizei i = 0; i < m_textureSlots.size(); ++i)
            {
                if (m_textureSlots[i] == tid)
                {
                    ts = static_cast<asl::f32>(i + 1);
                    foundTextureID = true;
                    break;
                }
            }

            if (!foundTextureID)
            {
                if (m_textureSlots.size() >= 32)
                {
                    end();
                    draw();
                    begin();
                }

                m_textureSlots.push_back(tid);
                ts = static_cast<asl::f32>(m_textureSlots.size() - 1);
            }
        }

        m_buffer->position =
            glm::vec2(renderable.pos.x, renderable.pos.y + size.y * scale);
        m_buffer->color = renderable.color;
        m_buffer->uv = glm::vec2(0.0f, 1.0f);
        m_buffer->textureID = ts;
        m_buffer++;

        m_buffer->position = glm::vec2(renderable.pos.x + size.x * scale,
                                       renderable.pos.y + size.y * scale);
        m_buffer->color = renderable.color;
        m_buffer->uv = glm::vec2(1.0f, 1.0f);
        m_buffer->textureID = ts;
        m_buffer++;

        m_buffer->position =
            glm::vec2(renderable.pos.x + size.x * scale, renderable.pos.y);
        m_buffer->color = renderable.color;
        m_buffer->uv = glm::vec2(1.0f, 0.0f);
        m_buffer->textureID = ts;
        m_buffer++;

        m_buffer->position = renderable.pos;
        m_buffer->color = renderable.color;
        m_buffer->uv = glm::vec2(0.0f, 0.0f);
        m_buffer->textureID = ts;
        m_buffer++;

        m_indexCount += 6;
    }

    template <typename Container>
    void
    BatchRenderer2D<tewi::API::OpenGLTag>::add(const Container& renderableList)
    {
        // TODO: Refactor this to make it actually work, like it did before the
        // vulkan shitshow
        for (const auto& renderable : renderableList)
        {
            add(renderable);
        }
    }
} // namespace tewi
