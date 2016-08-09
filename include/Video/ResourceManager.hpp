#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <string>
#include <map>

#include "Video/TextureCache.h"

template <class CacheType>
class ResourceManager
{
public:
	static auto getResource(const std::string& path);
private:
	static CacheType m_cache;
};


template <class CacheType>
CacheType ResourceManager<CacheType>::m_cache;

template <class CacheType>
auto ResourceManager<CacheType>::getResource(const std::string& path)
{
	return m_cache.get(path);
}

#endif /* RESOURCE_MANAGER_H */
