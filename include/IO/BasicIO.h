#pragma once

#include <vector>
#include <string>
#include <fstream>

#include "Log.h"

#include "asl/filesystem"
#include "asl/types"

#include "Common.h"

namespace tewi
{
	namespace IO
	{
		template <typename T>
		inline TEWI_EXPORT std::vector<T> fileToBuffer(const std::string& path)
		{
			std::ifstream file(path, std::ios::binary);

			TEWI_EXPECTS(!file.fail(), "Can't open file " + path);

			file.seekg(0, std::ios::end);

			int fileSize = file.tellg();

			std::vector<T> buffer(fileSize);

			// This cast.
			file.read((char*)(&buffer[0]), fileSize);

			return buffer;
		}

		template <typename T>
		inline TEWI_EXPORT bool fileToBuffer(const std::string& path, std::vector<T>& buffer)
		{
			std::ifstream file(path, std::ios::binary);
			TEWI_EXPECTS(!file.fail(), "Can't open file " + path);

			//seek to the end
			file.seekg(0, std::ios::end);

			//Get the file size
			int fileSize = file.tellg();
			file.seekg(0, std::ios::beg);

			//Reduce the file size by any header bytes that might be present
			fileSize -= file.tellg();

			buffer.resize(fileSize);
			file.read((char *)&(buffer[0]), fileSize);
			file.close();

			return true;
		}

		inline TEWI_EXPORT std::string removeExtension(const std::string& str)
		{
			asl::sizei index = str.find_last_of('.');
			return str.substr(0, index);
		}

		using Path = std::pair<bool, std::string>;

		template <typename Container>
		inline TEWI_EXPORT Path findCorrectFile(const std::string& path, const Container& acceptedExtensions)
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
		inline TEWI_EXPORT Path findCorrectFile(const std::string& path, const Container1& acceptedExtensions, const Container2& regexHelpers)
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
