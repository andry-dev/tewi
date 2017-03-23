#pragma once

#include <glm/glm.hpp>

#include <GL/glew.h>

#include "Video/Vertex.h"
#include "Video/Renderable2D.hpp"
#include "Video/IndexBuffer.hpp"
#include "Log.h"
#include "Common.h"

#include "Video/BatchRenderer2D.hpp"

#include <array>
#include <memory>
#include <cstddef>
#include <algorithm>

#include "asl/types"

namespace tewi
{
	constexpr asl::sizei g_maxTextures = 64000;
	constexpr asl::sizei g_vertexSize = sizeof(Vertex);
	constexpr asl::sizei g_spriteSize = g_vertexSize * 4;
	constexpr asl::sizei g_bufferSize = g_spriteSize * g_maxTextures;
	constexpr asl::sizei g_indicesSize = g_maxTextures * 6;

	constexpr asl::num g_posAttribPointer = 0;
	constexpr asl::num g_uvAttribPointer = 1;
	constexpr asl::num g_tidAttribPointer = 2;
	constexpr asl::num g_colorAttribPointer = 3;

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
	struct BatchRenderer2D<API::OpenGLTag>
	{
	protected:
		BatchRenderer2D()
			: m_indexCount(0)
		{
			glGenVertexArrays(1, &m_VAO);
			glGenBuffers(1, &m_VBO);

			glBindVertexArray(m_VAO);
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			glBufferData(GL_ARRAY_BUFFER, g_bufferSize, 0, GL_DYNAMIC_DRAW);

			glEnableVertexAttribArray(g_posAttribPointer);
			glEnableVertexAttribArray(g_uvAttribPointer);
			glEnableVertexAttribArray(g_tidAttribPointer);
			glEnableVertexAttribArray(g_colorAttribPointer);

			glVertexAttribPointer(g_posAttribPointer, 2, GL_FLOAT, GL_FALSE, g_vertexSize, reinterpret_cast<const void*>(0));
			glVertexAttribPointer(g_uvAttribPointer, 2, GL_FLOAT, GL_FALSE, g_vertexSize, reinterpret_cast<const void*>(offsetof(Vertex, uv)));
			glVertexAttribPointer(g_colorAttribPointer, 4, GL_UNSIGNED_BYTE, GL_TRUE, g_vertexSize, reinterpret_cast<const void*>(offsetof(Vertex, color)));
			glVertexAttribPointer(g_tidAttribPointer, 1, GL_FLOAT, GL_FALSE, g_vertexSize, reinterpret_cast<const void*>(offsetof(Vertex, textureID)));


			glBindBuffer(GL_ARRAY_BUFFER, 0);

			std::vector<GLuint> indices(g_indicesSize);
			for (asl::mut_sizei i = 0, offset = 0; i < indices.size(); i += 6, offset += 4)
			{
				indices[  i  ] = offset + 0;
				indices[i + 1] = offset + 1;
				indices[i + 2] = offset + 2;

				indices[i + 3] = offset + 2;
				indices[i + 4] = offset + 3;
				indices[i + 5] = offset + 0;
			}

			m_IBO = std::make_unique<IndexBuffer<GLuint>>(indices);

			glBindVertexArray(0);
			Log::debugInfo("BatchRenderer2D<GL>::BatchRenderer2D");
		}

		~BatchRenderer2D()
		{
			Log::debugInfo("BatchRenderer2D<GL>::~BatchRenderer2D");
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
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			m_buffer = (Vertex*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
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
		void add(const Renderable2D& renderable)
		{
			const auto& position = renderable.pos;
			const auto& color = renderable.color;
			const auto& size = renderable.texture.size;
			const auto tid = renderable.texture.id;
			const auto scale = renderable.scale;

			float ts = 0;

			if (tid > 0)
			{
				bool foundTextureID = false;
				for (asl::mut_sizei i = 0; i < m_textureSlots.size(); ++i)
				{
					if (m_textureSlots[i] == tid)
					{
						ts = i + 1;
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
					ts = m_textureSlots.size() - 1;
				}
			}

			m_buffer->position = glm::vec2(position.x, position.y + size.y * scale);
			m_buffer->color = color;
			m_buffer->uv = glm::vec2(0.0f, 1.0f);
			m_buffer->textureID = ts;
			m_buffer++;

			m_buffer->position = glm::vec2(position.x + size.x * scale, position.y + size.y * scale);
			m_buffer->color = color;
			m_buffer->uv = glm::vec2(1.0f, 1.0f);
			m_buffer->textureID = ts;
			m_buffer++;

			m_buffer->position = glm::vec2(position.x + size.x * scale, position.y);
			m_buffer->color = color;
			m_buffer->uv = glm::vec2(1.0f, 0.0f);
			m_buffer->textureID = ts;
			m_buffer++;

			m_buffer->position = position;
			m_buffer->color = color;
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
		void add(const std::vector<Renderable2D>& renderableList)
		{
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
			for (asl::mut_sizei i = 0; i < m_textureSlots.size(); ++i)
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

	private:
		GLuint m_VBO;
		GLuint m_VAO;
		Vertex* m_buffer;
		std::vector<GLuint> m_textureSlots;
		std::unique_ptr<IndexBuffer<GLuint>> m_IBO;
		asl::mut_sizei m_indexCount;
	};
}