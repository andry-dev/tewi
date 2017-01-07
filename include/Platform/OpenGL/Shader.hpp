#pragma once

#include <utility>
#include <fstream>
#include <string>

#include "Utils/Types.h"

#include "GL/glew.h"

#include "Video/API/Shader.hpp"
#include "Video/API/API.h"

#include "Log.h"
#include "IO/BasicIO.h"

#include "Utils/Functional.h"

namespace tewi
{
	namespace API
	{
		namespace
		{
			constexpr std::array<const char*, 7> g_shaderExts = { {
				".vert",
					".frag",
					".tesc",
					".tese",
					".geom",
					".frag",
					".comp"
			} };
		}

		template <>
		class Shader<API_TYPE::OPENGL>
		{
		public:
			Shader(const std::string& vertPath, const std::string& fragPath)
				: m_vertPath(IO::findCorrectFile(vertPath, g_shaderExts))
				, m_fragPath(IO::findCorrectFile(fragPath, g_shaderExts))
				, m_vertID([] { return glCreateShader(GL_VERTEX_SHADER); }())
				, m_fragID([] { return glCreateShader(GL_FRAGMENT_SHADER); }())
				, m_programID(0)
				, m_attribNum(0)
			{
				Expects(m_vertID != 0, "Can't create vertex shader");
				Expects(m_fragID != 0, "Can't create fragment shader");

				compile(m_vertPath, m_vertID);
				compile(m_fragPath, m_fragID);

				m_programID = glCreateProgram();
			}
			
			~Shader() = default;
		
			Shader(const Shader& rhs) = default;
			Shader& operator=(const Shader& rhs) = default;
		
			Shader(Shader&& rhs) = default;
			Shader& operator=(Shader&& rhs) = default;


			void link()
			{
				glAttachShader(m_programID, m_vertID);
				glAttachShader(m_programID, m_fragID);
				
				glLinkProgram(m_programID);

				mut_num res = 0;
				glGetShaderiv(m_programID, GL_LINK_STATUS, &res);

				if (res == GL_FALSE)
				{
					int maxLen = 0;
					glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &maxLen);

					std::vector<GLchar> errorLog(maxLen);

					glGetProgramInfoLog(m_programID, maxLen, &maxLen, &errorLog[0]);

					Log::warning(errorLog.data());

					glDeleteProgram(m_programID);
					glDeleteShader(m_vertID);
					glDeleteShader(m_fragID);

					Expects(0, "Shader failed to link");
				}

				glDetachShader(m_programID, m_vertID);
				glDetachShader(m_programID, m_fragID);
				glDeleteShader(m_vertID);
				glDeleteShader(m_fragID);
			}

			void enable()
			{
				glUseProgram(m_programID);
				for (mut_sizei i = 0; i < m_attribNum; ++i)
				{
					glEnableVertexAttribArray(i);
				}
			}

			void disable()
			{
				glUseProgram(0);
				for (mut_sizei i = 0; i < m_attribNum; ++i)
				{
					glDisableVertexAttribArray(i);
				}
			}

			void addAtrib(const std::string& attribute)
			{
				glBindAttribLocation(m_programID, m_attribNum++, attribute.c_str());
			}

			void addAttrib(const std::initializer_list<std::string>& args)
			{
				for (const auto& attrib : args)
				{
					glBindAttribLocation(m_programID, m_attribNum++, attrib.c_str());
				}
			}

			u32 getUniformLocation(const std::string& uniformName)
			{
				u32 location = glGetUniformLocation(m_programID, uniformName.c_str());
				Expects(location != GL_INVALID_INDEX, "Invalid uniform variable " + uniformName);
				return location;
			}

			template <unsigned long N>
			std::array<u32, N> getUniformLocation(const std::array<const char*, N>& uniformName)
			{
				std::array<u32, N> arr;

				for (int i = 0; i < N; ++i)
				{
					u32 location = glGetUniformLocation(m_programID, uniformName[i]);
					Expects(location != GL_INVALID_INDEX, "Invalid uniform variable " + uniformName);
					arr[i] = location;
				}

				return arr;
			}

		private:

			void compile(const std::string& path, u32 id)
			{
				std::ifstream shaderFile(path);

				std::string content;
				
				// Fuckery to read a file
				shaderFile.seekg(0, std::ios::end);
				content.resize(shaderFile.tellg());
				shaderFile.seekg(0, std::ios::beg);
				shaderFile.read(&content[0], content.size());

				auto str_ptr = content.c_str();
				glShaderSource(id, 1, &str_ptr, nullptr);
				glCompileShader(id);

				mut_num res = 0;
				glGetShaderiv(id, GL_COMPILE_STATUS, &res);

				if (res == GL_FALSE)
				{
					mut_num maxLen = 0;
					glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLen);

					std::vector<GLchar> errorLog(maxLen);

					glGetShaderInfoLog(id, maxLen, &maxLen, errorLog.data());
					Log::warning(errorLog.data());
					Expects(false, "Shader " + path + " failed to compile");
				}
			}

			std::string m_vertPath;
			std::string m_fragPath;

			u32 m_vertID;
			u32 m_fragID;
			mut_u32 m_programID;
			mut_u32 m_attribNum;
		};
	} // namespace API
} // namespace tewi
