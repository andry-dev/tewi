#include "Video/BatchRenderer2D.h"

#include <SDL2/SDL.h>
#include <cstddef>
#include "Log.h"

namespace tewi
{
	namespace Video
	{
		BatchRenderer2D::BatchRenderer2D()
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

			glVertexAttribPointer(g_posAttribPointer, 3, GL_FLOAT, GL_FALSE, g_vertexSize, reinterpret_cast<const void*>(0));
			glVertexAttribPointer(g_uvAttribPointer, 2, GL_FLOAT, GL_FALSE, g_vertexSize, reinterpret_cast<const void*>(offsetof(Vertex, uv)));
			glVertexAttribPointer(g_tidAttribPointer, 1, GL_UNSIGNED_INT, GL_FALSE, g_vertexSize, reinterpret_cast<const void*>(offsetof(Vertex, textureID)));
			glVertexAttribPointer(g_colorAttribPointer, 4, GL_UNSIGNED_BYTE, GL_TRUE, g_vertexSize, reinterpret_cast<const void*>(offsetof(Vertex, color)));

			glBindBuffer(GL_ARRAY_BUFFER, 0);

			std::vector<GLuint> indices(g_indicesSize);
			for (std::size_t i = 0, offset = 0; i < indices.size(); i += 6, offset += 4)
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
		}

		BatchRenderer2D::~BatchRenderer2D()
		{
			glDeleteBuffers(1, &m_VBO);
		}

		void BatchRenderer2D::begin()
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			m_buffer = (Vertex*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		}

		void BatchRenderer2D::add(const Renderable2D* renderable)
		{
			const auto& position = renderable->getPosition();
			const auto& color = renderable->getColor();
			const auto& size = renderable->getSize();
			const auto tid = renderable->getTextureID();

			auto ts = 0;
			if (tid > 0)
			{
				bool foundTextureID = false;
				for (int i = 0; i < m_textureSlots.size(); ++i)
				{
					if (m_textureSlots[i] == tid)
					{
						ts = i + i;
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
					ts = m_textureSlots.size();
				}
			}

			//Logi("Vertex position is " + std::to_string(position.x) + ", " + std::to_string(position.y));
			//Logi("Size is " + std::to_string(size.x) + ", " + std::to_string(size.y));


			m_buffer->position = glm::vec3(position.x, position.y + size.y, position.z);
			m_buffer->color = color;
			m_buffer->uv = glm::vec2(0.0f, 1.0f);
			m_buffer++;

			m_buffer->position = glm::vec3(position.x + size.x, position.y + size.y, position.z);
			m_buffer->color = color;
			m_buffer->uv = glm::vec2(1.0f, 1.0f);
			m_buffer->textureID = ts;
			m_buffer++;

			m_buffer->position = glm::vec3(position.x + size.x, position.y, position.z);
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

		void BatchRenderer2D::draw()
		{
			for (std::size_t i = 0; i < m_textureSlots.size(); ++i)
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

		void BatchRenderer2D::end()
		{
			glUnmapBuffer(GL_ARRAY_BUFFER);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	}
}
