#pragma once

#include "tewi/Video/TextureCache.h"

#include <vector>
#include <cstdlib>

#include "stb_image.h"

#include "tewi/IO/BasicIO.h"
#include "tewi/Utils/Log.h"

#include "asl/debug_only"
#include "asl/meta"

namespace tewi
{

    namespace API
    {
        template <typename APIType>
        void genAPITexture(Texture<APIType>& tex, asl::u8* imagePtr, asl::num width, asl::num height);
        #if 0
        {
            static_assert(asl::disable_type_v<APIType>, "\n"
                    "You need to override this function to load textures. The correct and only way to do so is to specialize it with the following signature: \n"
                    "\n"
                    "template <> \n"
                    "void genAPITexture(Texture<~YourTagHere~>& tex, ~the other parameters here~) \n"
                    "{ ... } \n"
                    "\n"
                    "Specifying the first 'template <>' is extremely important: failing to do so will result in some compilers discarding your function and you trying to figure out why your function is not getting called.\n"
                    "Yes, this sucks.");

        }
        #endif
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

        asl::num width = 0;
        asl::num height = 0;
        asl::num chan = 0;

        asl::u8* imagePtr = stbi_load(path.c_str(), &width, &height,
                                         &chan, STBI_rgb_alpha);


        TEWI_ENSURES(imagePtr != nullptr, "[TextureCache<T>::load] Can't decode PNG " + path);

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
