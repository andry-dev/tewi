#ifndef BATCH_RENDERER_2D_H
#define BATCH_RENDERER_2D_H

#include <glm/glm.hpp>

#include <GL/glew.h>

#include "Video/Vertex.h"
#include "Video/Renderable2D.hpp"
#include "Video/IndexBuffer.hpp"

#include <array>
#include <memory>

namespace tewi
{
	namespace Video
	{
		constexpr size_t g_maxTextures = 64000;
		constexpr size_t g_vertexSize = sizeof(Video::Vertex);
		constexpr size_t g_spriteSize = g_vertexSize * 4;
		constexpr size_t g_bufferSize = g_spriteSize * g_maxTextures;
		constexpr size_t g_indicesSize = g_maxTextures * 6;

		constexpr int g_posAttribPointer = 0;
		constexpr int g_uvAttribPointer = 1;
		constexpr int g_tidAttribPointer = 2;
		constexpr int g_colorAttribPointer = 3;

		class BatchRenderer2D
		{
		public:
			BatchRenderer2D();
			~BatchRenderer2D();

			BatchRenderer2D(const BatchRenderer2D& rhs) = delete;
			BatchRenderer2D& operator=(const BatchRenderer2D& rhs) = delete;

			BatchRenderer2D(BatchRenderer2D&& rhs) =  delete;
			BatchRenderer2D& operator=(BatchRenderer2D&& rhs) = delete;

			void begin();

			void add(const Renderable2D* renderable);
			void draw();
			
			void end();
		private:
			GLuint m_VBO;
			GLuint m_VAO;
			Vertex* m_buffer;
			std::vector<GLuint> m_textureSlots;
			std::unique_ptr<IndexBuffer<GLuint>> m_IBO;
			std::size_t m_indexCount;
		};
	}
}

#endif /* BATCH_RENDERER_2D_H */
