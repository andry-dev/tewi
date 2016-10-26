#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <cstdint>
#include <vector>

#include "Utils/String.hpp"

namespace tewi
{
	namespace Video
	{
		class Shader
		{
		public:
			Shader(const Utils::String& vertPath, const Utils::String& fragPath);
			~Shader();
			
			void addAttrib(const Utils::String& attrib);
			void addAttrib(std::initializer_list<std::string> args);

			std::uint32_t getUniformLocation(const Utils::String& uniformName);
			std::vector<std::uint32_t> getUniformLocation(std::initializer_list<const Utils::String> uniformsName);

			void link();
			void enable();
			void disable();
		private:

			void compile(const Utils::String& path, int id);
			
			std::uint32_t m_programID = 0;

			std::uint32_t m_vertShaderID = 0;
			std::uint32_t m_fragShaderID = 0;

			int m_attribNum = 0;

			Utils::String m_vertShaderPath;
			Utils::String m_fragShaderPath;
		};
	}
}

#endif /* SHADER_H */
