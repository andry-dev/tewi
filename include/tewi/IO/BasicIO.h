#pragma once

#include <fstream>
#include <string>
#include <vector>

#include "tewi/Utils/Log.h"

#include "asl/filesystem"
#include "asl/types"

#include "tewi/Common.h"

namespace tewi
{
    namespace IO
    {
        inline TEWI_EXPORT std::string readFileContents(const std::string& path)
        {
            FILE* shaderFile = std::fopen(path.c_str(), "r");
            std::fseek(shaderFile, 0, SEEK_END);
            const asl::isize length = std::ftell(shaderFile);

            std::string content(static_cast<const asl::usize>(length), '\0');

            std::fseek(shaderFile, 0, SEEK_SET);
            std::fread(&content[0], 1, static_cast<const asl::usize>(length),
                       shaderFile);
            std::fclose(shaderFile);

            return content;
        }

        inline TEWI_EXPORT std::string removeExtension(const std::string& str)
        {
            return str.substr(0, str.find_last_of('.'));
        }

        using Path = std::pair<bool, std::string>;

        template <typename Container>
        inline TEWI_EXPORT Path findCorrectFile(
            const std::string& path, const Container& acceptedExtensions)
        {
            // TODO: This is too slow 07-01-2017
            // Even if we optimized for the best case (path is generic, so
            // it doesn't exist), this is still too slow (becase this is
            // basically a bruteforce)
            //
            // The calls are identical, maybe I can fix them in some way
            //
            // We should go with a regex:
            // If we match some words (like vert) then we should first try
            // with related extension (so .vert in this case)

            if (!asl::fs::fileExists(path.c_str()))
            {
                auto newPath = removeExtension(path);

                // First we try by removing the extension
                for (const auto& ext : acceptedExtensions)
                {
                    std::string pathWithNewExt = newPath + ext;
                    if (asl::fs::fileExists(pathWithNewExt.c_str()))
                    {
                        return { true, pathWithNewExt };
                    }
                }

                // If it fails we just try to append the extension
                for (const auto& ext : acceptedExtensions)
                {
                    std::string pathWithNewExt = path + ext;
                    if (asl::fs::fileExists(pathWithNewExt.c_str()))
                    {
                        return { true, pathWithNewExt };
                    }
                }

                return { false, "" };
            }
            else
            {
                return { true, path };
            }

            TEWI_EXPECTS(0, "Can't find file " + path);
            return { false, "" };
        }

        template <typename Container1, typename Container2>
        inline TEWI_EXPORT Path
        findCorrectFile(const std::string& path,
                        const Container1& acceptedExtensions, const Container2&)
        {
            auto res = findCorrectFile(path, acceptedExtensions);

            if (res.first)
            {
                return res;
            }
            else
            {
                TEWI_EXPECTS(0, "Not implemented yet");
            }

            return { false, "" };
        }

    } // namespace IO
} // namespace tewi
