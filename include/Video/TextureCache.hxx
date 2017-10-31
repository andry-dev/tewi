#include "Video/TextureCache.h"

#include <vector>

#include <cstdlib>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "IO/BasicIO.h"
#include "Log.h"
#include "asl/debug_only"

namespace tewi
{

    namespace API
    {
        template <typename APIType>
        void genAPITexture(Texture<APIType>& tex, asl::mut_u8* imagePtr, asl::num width, asl::num height)
        {
        }
    } // namespace API

    template <typename APIType>
    Texture<APIType> TextureCache<APIType>::get(const std::string& path)
    {
        auto it = m_map.find(path);

        if (it == m_map.end())
        {
            Texture<APIType> tex = load(path);
            m_map.insert(std::make_pair(path, tex));
            Log::debugInfo("Inserted texture " + path);
            return tex;
        }

        Log::debugInfo("Loaded cached texture " + path);
        return it->second;
    }

    template <typename APIType>
    Texture<APIType> TextureCache<APIType>::load(const std::string& path)
    {
        Texture<APIType> tex = {};

        int width = 0;
        int height = 0;
        int chan = 0;

        asl::mut_u8* imagePtr = stbi_load(path.c_str(), &width, &height,
                                         &chan, STBI_rgb_alpha);

        TEWI_EXPECTS(imagePtr != nullptr, "Can't decode PNG " + path);

        tex.size = glm::vec2(width, height);

#ifdef TEWI_TEXTURE_ENABLE_PIXELS
        tex.pixels.resize(width * height * 4);
        memcpy(&tex.pixels[0], imagePtr, tex.pixels.size());
#endif /* TEWI_TEXTURE_ENABLE_PIXELS */

        API::genAPITexture(tex, imagePtr, width, height);

        stbi_image_free(imagePtr);

        return tex;
    }
} // namespace tewi

#include "Platform/OpenGL/TextureCache.hpp"
