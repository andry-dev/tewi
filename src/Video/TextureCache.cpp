#include "Video/TextureCache.h"

#include <vector>

#include <GL/glew.h>

#include "lodepng/picopng.h"
#include "IO/BasicIO.h"
#include "Log.h"
#include "Utils/DebugOnly.h"

namespace tewi
{
	namespace Video
	{
		TextureCache::TextureCache()
		{

		}

		TextureCache::~TextureCache()
		{

		}

		Texture TextureCache::get(const std::string& path)
		{
			auto it = m_map.find(path);

			if (it == m_map.end())
			{
				Texture tex = load(path);
				m_map.insert(std::make_pair(path, tex));
				Logi("Inserted texture " + path);
				return tex;
			}

			Logi("Loaded cached texture " + path);
			return it->second;
		}

		Texture TextureCache::load(const std::string& path)
		{
			Texture tex = {};

			std::vector<unsigned char> out;
			std::vector<unsigned char> in;
			DebugOnly<bool> loadedPNG = IO::fileToBuffer(path, in);
			Expects(loadedPNG, "Failed to load PNG " + path);

			unsigned long width, height;

			DebugOnly<int> errCode = decodePNG(out, width, height, &in[0], in.size());
			Expects(errCode == 0, "Can't decode PNG " + path + " \nError code is " + std::to_string(errCode));

			glGenTextures(1, &tex.id);

			glBindTexture(GL_TEXTURE_2D, tex.id);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &out[0]);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

			glGenerateMipmap(GL_TEXTURE_2D);

			glBindTexture(GL_TEXTURE_2D, 0);

			tex.width = width;
			tex.height = height;

			return tex;
		}
	}
}
