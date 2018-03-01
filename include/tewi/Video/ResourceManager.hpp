#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <string>
#include <map>

#include "tewi/Common.h"
#include "tewi/Video/TextureCache.h"

namespace tewi
{
    /** \brief Generic resource manager
     *
     * It basically retrieves resources by using whatever class that implements a \a get() function.
     *
     *
     * Example:
     *
     * \code
     *
     * // Let's say we need a specific resource that tewi doesn't implement.
     * // For example, at the moment tewi lacks support for audio, so we may want to do this:
     *
     * struct Audio
     * {
     *     std::string path;
     *     int channels;
     *     // And whatever we need
     * };
     *
     * // Then we can create an AudioCache or whatever system that simply retrieves an audio file and stores it in a temporary variable.
     *
     * class AudioCache
     * {
     * public:
     *     Audio get(const std::string& path)
     *     {
     *         Audio audioFile = {};
     *
     *         // Implementation.
     *         // [...]
     *
     *         return audioFile;
     *     }
     *
     * private:
     *     // Whatever you want.
     *
     * };
     *
     * // And we can then use it in this ResourceManager to retrive the resource:
     *
     * // Somewhere in the code.
     * {
     *
     *     Audio audioTrack = ResourceManager<AudioCache>::getResource("path/to/the/file.ogg");
     *
     * }
     *
     * And we're done
     *
     * \endcode
     *
     * "What is the point in this if I can just create my static class to use the resource?"
     *
     * This is just a common interface that I built to simplify my work, nothing stops you from not using it.
     *
     */
    template <typename APIType, template <typename> class CacheType>
    class ResourceManager
    {
    public:
        static auto getResource(const std::string& path);
    private:
        static CacheType<APIType> m_cache;
    };

    template <typename APIType, template <typename> class CacheType>
    CacheType<APIType> ResourceManager<APIType, CacheType>::m_cache;

    template <typename APIType, template <typename> class CacheType>
    inline auto ResourceManager<APIType, CacheType>::getResource(const std::string& path)
    {
        return m_cache.get(path);
    }
}

#endif /* RESOURCE_MANAGER_H */
