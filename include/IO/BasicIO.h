#ifndef BASIC_IO_H
#define BASIC_IO_H

#include <vector>
#include <string>
#include <fstream>

#include "Log.h"

namespace tewi
{
	namespace IO
	{
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
	}
}

#endif /* BASIC_IO_H */
