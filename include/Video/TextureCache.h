#ifndef TEXTURE_CACHE_H
#define TEXTURE_CACHE_H

#include <map>
#include "Video/Texture.h"

namespace tewi
{
	namespace Video
	{
		class TextureCache
		{
		public:
			TextureCache();
			~TextureCache();

			Texture get(const std::string& path);

		private:
			Texture load(const std::string& path);
			std::map<std::string, Texture> m_map;
		};
	}
}


#endif /* TEXTURE_CACHE_H */
