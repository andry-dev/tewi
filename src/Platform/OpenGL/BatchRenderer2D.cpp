#include <array>
#include <memory>
#include <cstddef>
#include <algorithm>

#include <GL/glew.h>
#include <glm/glm.hpp>

#include "tewi/Common.h"
#include "tewi/Video/Vertex.h"
#include "tewi/Video/Renderable2D.hpp"
#include "tewi/Video/IndexBuffer.hpp"
#include "tewi/Video/API/Device.hpp"
#include "tewi/Video/BatchRenderer2D.hpp"
#include "tewi/Video/Uniform.h"
#include "tewi/Utils/Log.h"

#include "asl/types"

namespace tewi
{

    /** \brief Batch renderer for 2D objects.
     *
     * This is a batch renderer for 2D objects.
     *
     * \a APINum is the number of the API that you want to use.
     *
     * To render a renderable:
     * * You first need to instantiate the class with the API number.
     * * Begin the batch with \a begin().
     * * Insert the renderables between \a begin() and \a end() with \a add().
     * * End the batch with \a end().
     * * Make the draw call with \a draw().
     *
     * Example:
     * \code
     *
     * using namespace tewi;
     * constexpr int api = API::API_TYPE::OPENGL;
     * BatchRenderer2D<api> batch;
     *
     * // Later in the code
     * // Let's assume that we have to render a sprite
     *
     * Sprite spr(glm::vec2(1.0f, 1.0f), "path/to/sprite.png");
     *
     * // In our draw function we do this:
     *
     * // First begin the batch
     * batch.begin();
     *
     * // ADD YOUR RENDERABLES HERE
     * batch.add(spr.getRenderable());
     *
     * // Then end the batch
     * batch.end();
     *
     * // And render it
     * batch.draw();
     *
     * \endcode
     *
     * Tips:
     * * \a add() additionally supports a vector of Renderable2D, so you can pack all the renderables in a vector and supply them to the renderer.
     */
    template <>
    struct TEWI_EXPORT BatchRenderer2D<API::OpenGLTag>
    {
    protected:

        BatchRenderer2D()
            : m_indexCount(0)
        {
            initBuffers();
            bindAttribPointers();
            finalInit();
        }

        ~BatchRenderer2D()
        {
            glDeleteBuffers(1, &m_VBO);
        }

        BatchRenderer2D(const BatchRenderer2D& rhs) = delete;
        BatchRenderer2D& operator=(const BatchRenderer2D& rhs) = delete;

        BatchRenderer2D(BatchRenderer2D&& rhs) = default;
        BatchRenderer2D& operator=(BatchRenderer2D&& rhs) = default;

        /** Begins the rendering by binding the buffers.
         *
         * That's the first function you need to call.
         *
         */
        void begin()
        {
            tewi::setUniform(1, g_texIndices);
            glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
            m_buffer = reinterpret_cast<Vertex*>(glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY));
        }

        /** Add a **single** renderables to the buffer.
         *
         * Call this function one or multiple time **after** \a begin() and **before** \a end().
         * 
         * Example:
         *
         * \code
         * // Assuming a BatchRenderer named "batch"
         * // Also assuming a Sprite named "spr"
         *
         * batch.add(spr.getRenderable());
         *
         * // Or, if the Sprite supports implicit conversion to a Renderable2D
         *
         * batch.add(spr);
         *
         * \endcode
         */
        template <typename T>
        void add(const Renderable2D<T>& renderable)
        {
            //const auto& position = renderable.pos;
            //const auto& color = renderable.color;
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

            m_buffer->position = glm::vec2(renderable.pos.x, renderable.pos.y + size.y * scale);
            m_buffer->color = renderable.color;
            m_buffer->uv = glm::vec2(0.0f, 1.0f);
            m_buffer->textureID = ts;
            m_buffer++;

            m_buffer->position = glm::vec2(renderable.pos.x + size.x * scale, renderable.pos.y + size.y * scale);
            m_buffer->color = renderable.color;
            m_buffer->uv = glm::vec2(1.0f, 1.0f);
            m_buffer->textureID = ts;
            m_buffer++;

            m_buffer->position = glm::vec2(renderable.pos.x + size.x * scale, renderable.pos.y);
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

        /** Add a **vector** of renderables to the buffer.
         *
         * Call this function one or multiple time **after** \a begin() and **before** \a end().
         * 
         * Example:
         *
         * \code
         * 
         * // Assuming a BatchRenderer named "batch"
         * // And assuming a std::vector of Renderable2Ds named "vec"
         *
         * batch.add(vec);
         *
         * \endcode
         *
         */
        template <typename Container>
        void add(const Container& renderableList)
        {
            // TODO: Refactor this to make it actually work, like it did before the vulkan shitshow
            for (const auto& renderable : renderableList)
            {
                add(renderable);
            }
        }

        /** Unbinds the buffers.
         *
         * Call this after adding the renderables with \a add() and before \a draw().
         *
         */
        void end()
        {
            glUnmapBuffer(GL_ARRAY_BUFFER);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }

        /** Does the draw call and resets the buffer.
         *
         * You need to do this **after** \a end().
         *
         * This is the last function you need to call.
         *
         */
        void draw()
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

            glBindTexture(GL_TEXTURE_2D, 0);

            m_indexCount = 0;
        }

        static ShaderProgram<API::OpenGLTag> createShaderProgram()
        {
            constexpr asl::string_view vertstr =
            R"(
            #version 430 core

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
            #version 430 core

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

            return ShaderProgram<API::OpenGLTag>({ shaders }, { attribs });

        }

    private:
        void initBuffers()
        {
            glGenVertexArrays(1, &m_VAO);
            glGenBuffers(1, &m_VBO);

            glBindVertexArray(m_VAO);
            glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
            glBufferData(GL_ARRAY_BUFFER, g_bufferSize, 0, GL_DYNAMIC_DRAW);

        }

        void bindAttribPointers()
        {
            // Position
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(tewi::Vertex), (const void*)(0));

            // UV
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(tewi::Vertex), (const void*)(offsetof(Vertex, uv)));

            // TID
            glEnableVertexAttribArray(2);
            glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(tewi::Vertex), (const void*)(offsetof(Vertex, textureID)));

            // Color
            glEnableVertexAttribArray(3);
            glVertexAttribPointer(3, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(tewi::Vertex), (const void*)(offsetof(Vertex, color)));
        }

        void finalInit()
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

        static constexpr std::array<int, 16> g_texIndices =
        {
            0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
            11, 12, 13, 14, 15
        };

    };

}


