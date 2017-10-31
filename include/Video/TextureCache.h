#ifndef TEWI_TEXTURE_CACHE_H
#define TEWI_TEXTURE_CACHE_H

#include <map>
#include "Video/Texture.h"

#include "Common.h"

namespace tewi
{
    /** \brief A cache-system for textures
     *
     * In particular, this uses an std::map to cache textures and retrieve them by path.
     *
     * \sa ResourceManager
     *
     */
    template <typename APIType>
    class TextureCache
    {
    public:
        Texture<APIType> get(const std::string& path);

    private:
        Texture<APIType> load(const std::string& path);
        
        std::map<std::string, Texture<APIType>> m_map;
    };
}


#include "TextureCache.hxx"

#endif /* TEWI_TEXTURE_CACHE_H */
