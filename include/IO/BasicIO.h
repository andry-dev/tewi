#pragma once

#include <vector>
#include <string>
#include <fstream>

#include "Log.h"

#include "Common.h"

#if TEWI_CXX17_FILESYSTEM
	#ifdef TEWI_CXX17_FILESYSTEM_EXPERIMENTAL
		#include <experimental/filesystem>
		namespace fs = std::experimental::filesystem;
	#else
		#include <filesystem>
		namespace fs = std::filesystem;
	#endif
#else
	#ifdef TEWI_WIN32
		#define WIN32_LEAN_AND_MEAN
		#include <windows.h>
	#elif defined(TEWI_POSIX)
		#include <sys/types.h>
		#include <sys/stat.h>
		#include <unistd.h>
	#elif defined(TEWI_UNKNOWN_PLATFORM)
		#error "[tewi/IO/BasicIO.h] Your platform is unsupported :("
	#endif
#endif

namespace tewi
{
	namespace IO
	{
		namespace details
		{
			#if !TEWI_CXX17_FILESYSTEM
			inline bool fileExists(const std::string& path)
			{
				#if defined(TEWI_WIN32)

					WIN32_FIND_DATA FindFileData;
					HANDLE handle = FindFirstFile(path.c_str(), &FindFileData);
					int found = handle != INVALID_HANDLE_VALUE;
					if (found) 
					{
						FindClose(handle);
					}
					return found;

				#elif defined(TEWI_POSIX)

					struct stat status;
					if(::stat(path.c_str(), &status) == 0)
					{
						return true;
					}
					else
					{
						return false;
					}

				#endif
			}
			#endif
		} // namespace details

		inline std::vector<unsigned char> fileToBuffer(const std::string& path)
		{
			std::ifstream file(path, std::ios::binary);

			Expects(!file.fail(), "Can't open file " + path);

			file.seekg(0, std::ios::end);

			int fileSize = file.tellg();

			std::vector<unsigned char> buffer(fileSize);

			// This cast.
			file.read((char*)(&buffer[0]), fileSize);

			return buffer;
		}

		inline bool fileToBuffer(const std::string& path, std::vector<unsigned char>& buffer)
		{
			std::ifstream file(path, std::ios::binary);
			Expects(!file.fail(), "Can't open file " + path);

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

		inline bool fileExists(const std::string& file)
		{
			#if TEWI_CXX17_FILESYSTEM

			return fs::exists(file);

			#else

			return details::fileExists(file);

			#endif
		}


		inline std::string removeExtension(const std::string& str)
		{
			sizei index = str.find_last_of(".");
			return str.substr(0, index);
		}

		using Path = std::pair<bool, std::string>;

		template <sizei N>
		Path findCorrectFile(const std::string& path, const std::array<const char*, N>& acceptedExtensions)
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

			if (!fileExists(path))
			{
				auto newPath = removeExtension(path);

				// First we try by removing the extension
				for (const auto& ext : acceptedExtensions)
				{
					auto pathWithNewExt = newPath + ext;
					if (IO::fileExists(pathWithNewExt))
					{
						return { true, pathWithNewExt };
					}
				}
				
				// If it fails we just try to append the extension
				for (const auto& ext : acceptedExtensions)
				{
					auto pathWithNewExt = path + ext;
					if (IO::fileExists(pathWithNewExt))
					{
						return { true, pathWithNewExt };
					}
				}
			}
			else
			{
				return { true, path };
			}

			Expects(0, "Can't find file " + path);
			return { false, "" };
		}

		template <sizei N1, sizei N2>
		Path findCorrectFile(const std::string& path, const std::array<const char*, N1>& acceptedExtensions, const std::array<const char*, N2>& regexHelpers)
		{
			auto res = findCorrectFile(path, acceptedExtensions);

			if (res.first)
			{
				return res;
			}
			else
			{
				Expects(0, "Not implemented yet");
			}

			return { false, "" };
		}

	} // namespace IO
} // namespace tewi
