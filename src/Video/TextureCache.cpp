#include "Video/TextureCache.h"

#include <vector>

#include <GL/glew.h>

#include <cstdlib>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include "IO/BasicIO.h"
#include "Log.h"
#include "Utils/DebugOnly.h"

namespace tewi
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
			Log::debugInfo("Inserted texture " + path);
			return tex;
		}

		Log::debugInfo("Loaded cached texture " + path);
		return it->second;
	}

	Texture TextureCache::load(const std::string& path)
	{
		Texture tex = {};

		int width = 0;
		int height = 0;
		int chan = 0;

		std::uint8_t* imagePtr = stbi_load(path.c_str(), &width, &height, &chan, STBI_rgb_alpha);
		Expects(imagePtr != nullptr, "Can't decode PNG " + path);

		tex.size = glm::vec2(width, height);

		tex.pixels.resize(width * height * 4);
		memcpy(&tex.pixels[0], imagePtr, tex.pixels.size());

		glGenTextures(1, &tex.id);

		glBindTexture(GL_TEXTURE_2D, tex.id);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imagePtr);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);

		stbi_image_free(imagePtr);

		return tex;
	}
}
