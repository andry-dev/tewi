#pragma once

#include <utility>
#include <fstream>
#include <string>

#include "asl/types"

#include "GL/glew.h"

#include "Video/API/Shader.hpp"
#include "Video/API/API.h"

#include "Log.h"
#include "IO/BasicIO.h"

#include "asl/functional"

namespace tewi
{
	namespace API
	{
		namespace
		{
			inline void compileGLShaders(const std::string& path, asl::u32 id)
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

				asl::mut_num res = 0;
				glGetShaderiv(id, GL_COMPILE_STATUS, &res);

				if (res == GL_FALSE)
				{
					asl::mut_num maxLen = 0;
					glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLen);

					std::vector<GLchar> errorLog(maxLen);

					glGetShaderInfoLog(id, maxLen, &maxLen, errorLog.data());
					Log::warning(errorLog.data());
					TEWI_EXPECTS(false, "Shader " + path + " failed to compile");
				}
			}
		}

		template <>
		class VertexShader<API_TYPE::OPENGL>
		{
		protected:
			auto create()
			{
				asl::u32 ret = glCreateShader(GL_VERTEX_SHADER);

				TEWI_EXPECTS(ret != 0, "Can't create OpenGL vertex shader");

				return ret;
			}

			void compile(const std::string& path, asl::u32 id)
			{
				compileGLShaders(path, id);
			}
		};

		template <>
		class FragmentShader<API_TYPE::OPENGL>
		{
		protected:
			auto create()
			{
				asl::u32 ret = glCreateShader(GL_FRAGMENT_SHADER);

				TEWI_EXPECTS(ret != 0, "Can't create OpenGL fragment shader");

				return ret;
			}

			void compile(const std::string& path, asl::u32 id)
			{
				compileGLShaders(path, id);
			}
		};

		template <>
		class ShaderProgram<API_TYPE::OPENGL>
		{
		public:
			template <typename... Shaders>
			ShaderProgram(ShaderPack<Shaders...> pack)
				: m_id(glCreateProgram())
				, m_attribNum(0)
			{
				asl::for_each_tuple(pack, [this] (auto& shader)
				{
					auto sid = shader.getID();
					glAttachShader(m_id, sid);
				});

				glLinkProgram(m_id);

				asl::mut_num res = 0;
				glGetShaderiv(m_id, GL_LINK_STATUS, &res);

				if (res == GL_FALSE)
				{
					int maxLen = 0;
					glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &maxLen);

					std::vector<GLchar> errorLog(maxLen);

					glGetProgramInfoLog(m_id, maxLen, &maxLen, &errorLog[0]);

					Log::warning(errorLog.data());

					glDeleteProgram(m_id);

					for_each_tuple(pack, [this] (auto& shader)
					{
						auto sid = shader.getID();
						glDeleteShader(sid);
					});

					TEWI_EXPECTS(0, "Shader failed to link");
				}

				for_each_tuple(pack, [this] (auto& shader)
				{
					auto sid = shader.getID();
					glDetachShader(m_id, sid);
					glDeleteShader(sid);
				});
			}

			~ShaderProgram()
			{
				glDeleteProgram(m_id);
			}

			void enable()
			{
				glUseProgram(m_id);
				for (asl::mut_sizei i = 0; i < m_attribNum; ++i)
				{
					glEnableVertexAttribArray(i);
				}
			}

			void disable()
			{
				glUseProgram(0);
				for (asl::mut_sizei i = 0; i < m_attribNum; ++i)
				{
					glDisableVertexAttribArray(i);
				}
			}

			void addAtrib(const std::string& attribute)
			{
				glBindAttribLocation(m_id, m_attribNum++, attribute.c_str());
			}

			template <unsigned long N>
			void addAttrib(const std::array<const char*, N>& args)
			{
				for (const auto& attrib : args)
				{
					glBindAttribLocation(m_id, m_attribNum++, attrib);
				}
			}

			asl::u32 getUniformLocation(const std::string& uniformName)
			{
				asl::u32 location = glGetUniformLocation(m_id, uniformName.c_str());
				TEWI_EXPECTS(location != GL_INVALID_INDEX, "Invalid uniform variable " + uniformName);
				return location;
			}

			template <unsigned long N>
			std::array<asl::u32, N> getUniformLocation(const std::array<const char*, N>& uniformName)
			{
				std::array<asl::u32, N> arr;

				for (int i = 0; i < N; ++i)
				{
					asl::u32 location = glGetUniformLocation(m_id, uniformName[i]);
					TEWI_EXPECTS(location != GL_INVALID_INDEX, "Invalid uniform variable " + uniformName);
					arr[i] = location;
				}

				return arr;
			}

		private:
			asl::u32 m_id;
			asl::mut_sizei m_attribNum;
		};

		template <template <asl::num> class ShaderTypePolicy,
				 template <typename> class ShaderFindPolicy>
		class Shader<API_TYPE::OPENGL, ShaderTypePolicy, ShaderFindPolicy>
			: private ShaderTypePolicy<API_TYPE::OPENGL>
			, private ShaderFindPolicy<ShaderTypePolicy<API_TYPE::OPENGL>>
		{
		public:
			using ShaderTypeImpl = ShaderTypePolicy<API_TYPE::OPENGL>;
			using ShaderFindImpl = ShaderFindPolicy<ShaderTypeImpl>;

			explicit Shader(Device<API_TYPE::OPENGL>&, const std::string& path)
				: m_path(ShaderFindImpl::getShaderPath(path))
				, m_id(ShaderTypeImpl::create())
			{
				ShaderTypeImpl::compile(m_path, m_id);
			}
			
			~Shader() = default;
		
			Shader(const Shader& rhs) = default;
			Shader& operator=(const Shader& rhs) = default;
		
			Shader(Shader&& rhs) = default;
			Shader& operator=(Shader&& rhs) = default;

			auto getID() const { return m_id; }

		private:
			asl::u32 m_id;
			std::string m_path;
		};
	} // namespace API
} // namespace tewi
