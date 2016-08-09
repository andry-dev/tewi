#include "Video/Sprite.h"

#include <array>
#include <cstddef>

#include "Video/Vertex.h"

#include "Video/ResourceManager.hpp"
#include "Video/TextureCache.h"

#include "Log.h"

namespace tewi
{
	namespace Video
	{
		Sprite::Sprite(float x, float y, float w, float h, const std::string& path)
			: m_xpos(x), m_ypos(y), m_width(w), m_height(h)
		{
			Log::info("Sprite::Sprite");
			m_texture = ResourceManager<TextureCache>::getResource(path);

			if (m_VBOID == 0)
			{
				glGenBuffers(1, &m_VBOID);
			}

			std::array<Vertex, 6> vertexData;

			// First Triangle
			vertexData[0].setPosition(m_xpos + m_width, m_ypos + m_height);
			vertexData[0].setUV(1.0f, 1.0f);

			vertexData[1].setPosition(m_xpos, m_ypos + m_height);
			vertexData[1].setUV(0.0f, 1.0f);

			vertexData[2].setPosition(m_xpos, m_ypos);
			vertexData[2].setUV(0.0f, 0.0f);

			// Second Triangle
			vertexData[3].setPosition(m_xpos, m_ypos);
			vertexData[3].setUV(0.0f, 0.0f);

			vertexData[4].setPosition(m_xpos + m_width, m_ypos);
			vertexData[4].setUV(1.0f, 0.0f);

			vertexData[5].setPosition(m_xpos + m_width, m_ypos + m_height);
			vertexData[5].setUV(1.0f, 1.0f);

			for (auto& v : vertexData)
			{
				v.setColors(255, 255, 255, 255);
			}

			glBindBuffer(GL_ARRAY_BUFFER, m_VBOID);
			glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(Vertex), vertexData.data(), GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		Sprite::~Sprite()
		{
			if (m_VBOID != 0)
			{
				glDeleteBuffers(1, &m_VBOID);
			}

			Log::info("Sprite::~Sprite");
		}

		void Sprite::draw()
		{
			glBindTexture(GL_TEXTURE_2D, m_texture.id);

			glBindBuffer(GL_ARRAY_BUFFER, m_VBOID);

			glEnableVertexAttribArray(0);

			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*> (offsetof(Vertex, position)));
			glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, color)));
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, uv)));

			glDrawArrays(GL_TRIANGLES, 0, 6);

			glDisableVertexAttribArray(0);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	}
}
