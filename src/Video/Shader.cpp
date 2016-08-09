#include "Video/Shader.h"

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <fstream>
#include <streambuf>

#include <vector>

#include "Log.h"

namespace tewi
{
	namespace Video
	{
		Shader::Shader(const std::string& vertPath, const std::string& fragPath)
			: m_vertShaderPath(vertPath), m_fragShaderPath(fragPath)
		{
			m_vertShaderID = glCreateShader(GL_VERTEX_SHADER);
			Expects(m_vertShaderID != 0, "Can't initialize vertex shader");

			m_fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);
			Expects(m_fragShaderID != 0, "Can't initialize fragment shader");

			compile(m_vertShaderPath, m_vertShaderID);
			compile(m_fragShaderPath, m_fragShaderID);
		}

		Shader::Shader(const std::string& objPath)
			: m_objPath(objPath)
		{

		}

		Shader::~Shader()
		{

		}

		void Shader::compile(const std::string& path, int id)
		{
			m_programID = glCreateProgram();

			std::ifstream shaderFile(path);
			Expects(!shaderFile.fail(), "Can't open" + path);

			// Get the content of the file in a string
			//
			std::string fileContent = "";
			std::string line;
			while (std::getline(shaderFile, line))
			{
				fileContent += line + '\n';
			}

			const char* contPtr = fileContent.c_str();
			glShaderSource(id, 1, &contPtr, nullptr);
			glCompileShader(id);

			int result = 0;
			glGetShaderiv(id, GL_COMPILE_STATUS, &result);
			if (result == GL_FALSE)
			{
				int maxLen = 0;
				glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLen);

				std::vector<GLchar> errorLog(maxLen);

				glGetShaderInfoLog(id, maxLen, &maxLen, &errorLog[0]);
				Log::warning(errorLog.data());
				Expects(0, "Shader " + path + " failed to compile");
			}
		}

		void Shader::link()
		{

			glAttachShader(m_programID, m_vertShaderID);
			glAttachShader(m_programID, m_fragShaderID);

			glLinkProgram(m_programID);

			int result = 0;
			glGetProgramiv(m_programID, GL_LINK_STATUS, &result);
			// I hate this.
			if (result == GL_FALSE)
			{
				int maxLen = 0;
				glGetShaderiv(m_programID, GL_INFO_LOG_LENGTH, &maxLen);

				std::vector<GLchar> errorLog(maxLen);

				glGetProgramInfoLog(m_programID, errorLog.size(), &maxLen, &errorLog[0]);

				Log::warning(errorLog.data());
				
				glDeleteProgram(m_programID);
				glDeleteShader(m_vertShaderID);
				glDeleteShader(m_fragShaderID);

				Expects(0, "Shader failed to link");
			}

			glDetachShader(m_programID, m_vertShaderID);
			glDetachShader(m_programID, m_fragShaderID);
			glDeleteShader(m_vertShaderID);
			glDeleteShader(m_fragShaderID);
		}

		void Shader::addAttrib(const std::string& attrib)
		{
			glBindAttribLocation(m_programID, m_attribNum++, attrib.c_str());
		}

		void Shader::addAttrib(std::initializer_list<std::string> args)
		{
			for (const auto& str : args)
			{
				glBindAttribLocation(m_programID, m_attribNum++, str.c_str());
			}
		}

		void Shader::enable()
		{
			glUseProgram(m_programID);
			for (int i = 0; i < m_attribNum; ++i) {
				glEnableVertexAttribArray(i);
			}
		}

		void Shader::disable()
		{
			glUseProgram(0);
			for (int i = 0; i < m_attribNum; ++i) {
				glDisableVertexAttribArray(i);
			}
		}

		std::int32_t Shader::getUniformLocation(const std::string& uniformName)
		{
			std::int32_t location = glGetUniformLocation(m_programID, uniformName.c_str());
			Expects(location != GL_INVALID_INDEX, "Invalid uniform variable" + uniformName);
			return location;
		}

		std::vector<std::int32_t> Shader::getUniformLocation(std::initializer_list<const std::string> uniformsName)
		{
			std::vector<std::int32_t> vec;

			for (const auto& s : uniformsName)
			{
				std::int32_t location = glGetUniformLocation(m_programID, s.c_str());
				Expects(location != GL_INVALID_INDEX, "Invalid uniform variable " + s);
				vec.push_back(location);
			}

			return vec;
		}
	}
}
