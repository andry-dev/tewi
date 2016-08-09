#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <cstdint>
#include <vector>

namespace tewi
{
	namespace Video
	{
		class Shader
		{
		public:
			Shader(const std::string& vertPath, const std::string& fragPath);
			Shader(const std::string& objPath);
			~Shader();
			
			void addAttrib(const std::string& attrib);
			void addAttrib(std::initializer_list<std::string> args);

			std::int32_t getUniformLocation(const std::string& uniformName);
			std::vector<std::int32_t> getUniformLocation(std::initializer_list<const std::string> uniformsName);

			void link();
			void enable();
			void disable();
		private:

			void compile(const std::string& path, int id);
			
			std::uint32_t m_programID = 0;

			std::uint32_t m_vertShaderID = 0;
			std::uint32_t m_fragShaderID = 0;

			int m_attribNum = 0;

			std::string m_vertShaderPath;
			std::string m_fragShaderPath;

			std::string m_objPath;
		};
	}
}

#endif /* SHADER_H */
