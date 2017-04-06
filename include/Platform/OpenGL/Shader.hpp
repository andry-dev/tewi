#pragma once

#include <utility>
#include <fstream>
#include <cstdio>
#include <string>

#include "asl/types"

#include "GL/glew.h"

#include "Video/Shader.hpp"
#include "Video/API/API.h"

#include "Log.h"
#include "IO/BasicIO.h"

#include "asl/functional"

namespace tewi
{
	namespace
	{
		inline void compileGLShaders(const std::string& path, asl::u32 id)
		{
			FILE* shaderFile = std::fopen(path.c_str(), "r");
			std::fseek(shaderFile, 0, SEEK_END);
			asl::sizei length = std::ftell(shaderFile);

			std::string content(length, '\0');

			std::fseek(shaderFile, 0, SEEK_SET);
			std::fread(&content[0], 1, length, shaderFile);
			std::fclose(shaderFile);

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
	class VertexShader<API::OpenGLTag>
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
			tewi::Log::debugInfo("Vertex shader path is: " + path);
			compileGLShaders(path, id);
		}
	};

	template <>
	class FragmentShader<API::OpenGLTag>
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
			tewi::Log::debugInfo("Fragment shader path is: " + path);
			compileGLShaders(path, id);
		}
	};

	template <>
	class ShaderProgram<API::OpenGLTag>
	{
	public:
		template <asl::sizei N, typename... Shaders>
		ShaderProgram(const std::array<const char*, N> attribs, const ShaderPack<Shaders...>& pack)
			: m_id(glCreateProgram())
			, m_attribNum(0)
		{
			asl::for_each_tuple(pack, [this] (auto& shader)
			{
				auto sid = shader.getID();
				glAttachShader(m_id, sid);
			});

			for (asl::mut_sizei i = 0; i < attribs.size(); ++i)
			{
				glBindAttribLocation(m_id, i, attribs[i]);
			}

			glLinkProgram(m_id);

			asl::mut_num res = 0;
			glGetProgramiv(m_id, GL_LINK_STATUS, &res);

			if (res == GL_FALSE)
			{
				int maxLen = 0;
				glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &maxLen);

				std::vector<GLchar> errorLog(maxLen);

				glGetProgramInfoLog(m_id, maxLen, &maxLen, &errorLog[0]);

				Log::warning(errorLog.data());

				glDeleteProgram(m_id);

				asl::for_each_tuple(pack, [] (auto& shader)
				{
					auto sid = shader.getID();
					glDeleteShader(sid);
				});

				TEWI_EXPECTS(0, "Shader failed to link");
			}

			asl::for_each_tuple(pack, [this] (auto& shader)
			{
				auto sid = shader.getID();
				glDetachShader(m_id, sid);
				glDeleteShader(sid);
			});
		}

		~ShaderProgram()
		{
			Log::debugInfo("ShaderProgram<GL>::~ShaderProgram");
			glDeleteProgram(m_id);
		}

		void enable()
		{
			Log::debugInfo("ShaderProgram<GL>::enable");
			glUseProgram(m_id);
			for (asl::mut_sizei i = 0; i < m_attribNum; ++i)
			{
				glEnableVertexAttribArray(i);
			}
		}

		void disable()
		{
			Log::debugInfo("ShaderProgram<OGL>::disable");
			glUseProgram(0);
			for (asl::mut_sizei i = 0; i < m_attribNum; ++i)
			{
				glDisableVertexAttribArray(i);
			}
		}

		asl::u32 getUniformLocation(const std::string& uniformName)
		{
			asl::u32 location = glGetUniformLocation(m_id, uniformName.c_str());
			TEWI_EXPECTS(location != GL_INVALID_INDEX, "Invalid uniform variable \"" + uniformName + "\"");
			return location;
		}

		template <asl::sizei N>
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

	template <template <typename> class ShaderTypePolicy,
			 template <typename> class ShaderFindPolicy>
	class Shader<API::OpenGLTag, ShaderTypePolicy, ShaderFindPolicy>
		: private ShaderTypePolicy<API::OpenGLTag>
		, private ShaderFindPolicy<ShaderTypePolicy<API::OpenGLTag>>
	{
	public:
		using ShaderTypeImpl = ShaderTypePolicy<API::OpenGLTag>;
		using ShaderFindImpl = ShaderFindPolicy<ShaderTypeImpl>;

		explicit Shader(API::Device<API::OpenGLTag>&, const std::string& path)
			: m_id(ShaderTypeImpl::create())
			, m_path(ShaderFindImpl::getShaderPath(path).second)
		{
			ShaderTypeImpl::compile(m_path, m_id);
		}
		
		~Shader() = default;
	
		Shader(const Shader& rhs) = default;
		Shader& operator=(const Shader& rhs) = default;
	
		Shader(Shader&& rhs) = default;
		Shader& operator=(Shader&& rhs) = default;

		auto getID() const { return m_id; }

		using api_num = API::OpenGLTag;

	private:
		asl::u32 m_id;
		std::string m_path;
	};
} // namespace tewi
