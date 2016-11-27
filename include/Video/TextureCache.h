#ifndef TEWI_TEXTURE_CACHE_H
#define TEWI_TEXTURE_CACHE_H

#include <map>
#include "Video/Texture.h"

namespace tewi
{
	/** \brief A cache-system for textures
	 *
	 * In particular, this uses an std::map to cache textures and retrieve them by path.
	 *
	 * \sa ResourceManager
	 *
	 */
	class TextureCache
	{
	public:
		Texture get(const std::string& path);

	private:
		Texture load(const std::string& path);
		
		std::map<std::string, Texture> m_map;
	};
}


#endif /* TEWI_TEXTURE_CACHE_H */
