#pragma once

#include <GL/glew.h>

#include "tewi/Video/API/API.h"
#include "tewi/Video/TextureCache.h"

namespace tewi
{
    namespace API
    {
        void genAPITexture(Texture<API::OpenGLTag>& tex, asl::mut_u8* imagePtr, asl::num width, asl::num height)
        {
            glGenTextures(1, &tex.id);

            glBindTexture(GL_TEXTURE_2D, tex.id);

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imagePtr);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

            glGenerateMipmap(GL_TEXTURE_2D);

            glBindTexture(GL_TEXTURE_2D, 0);
        }
    } // namepsace API
} // namespace tewi
