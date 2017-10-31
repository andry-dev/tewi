#pragma once

#include <utility>
#include <fstream>
#include <cstdio>
#include <string>
#include <vector>


#include "GL/glew.h"

#include "Video/Shader.hpp"
#include "Video/API/API.h"

#include "Log.h"
#include "IO/BasicIO.h"

#include "asl/functional"

#include "Common.h"

namespace tewi
{
    namespace
    {
        inline TEWI_EXPORT void compileGLSL(const std::string& shadertext, asl::u32 id)
        {
            auto str_ptr = shadertext.c_str();

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
                TEWI_EXPECTS(false, "Shader failed to compile");
            }

        }

    } // namespace

    template <>
    class TEWI_EXPORT VertexShader<API::OpenGLTag>
    {
    public:
        using api_type = API::OpenGLTag;
    protected:
        auto create()
        {
            asl::u32 ret = glCreateShader(GL_VERTEX_SHADER);

            TEWI_EXPECTS(ret != 0, "Can't create OpenGL vertex shader");

            return ret;
        }

        void compile(const std::string& shadertext, asl::u32 id)
        {
            compileGLSL(shadertext, id);
        }
    };

    template <>
    class TEWI_EXPORT FragmentShader<API::OpenGLTag>
    {
    public:
        using api_type = API::OpenGLTag;
    protected:
        auto create()
        {
            asl::u32 ret = glCreateShader(GL_FRAGMENT_SHADER);

            TEWI_EXPECTS(ret != 0, "Can't create OpenGL fragment shader");

            return ret;
        }

        void compile(const std::string& path, asl::u32 id)
        {
            compileGLSL(path, id);
        }
    };

    template <>
    class TEWI_EXPORT ShaderProgram<API::OpenGLTag>
    {
    public:
        template <typename Container,
                 typename... Shaders,
                 std::enable_if_t<
                     !std::is_same<
                         std::decay_t<typename Container::value_type>,
                         const char*>::value,
                 bool> = false>
        ShaderProgram(const Container& attribs, Shaders&&... pack)
            : m_id(glCreateProgram())
            , m_attribNum(0)
        {
            asl::for_each_arg([this] (auto& shader)
            {
                auto sid = shader.getID();
                glAttachShader(m_id, sid);
            }, std::forward<Shaders>(pack)...);

            for (asl::mut_sizei i = 0; i < attribs.size(); ++i)
            {
                glBindAttribLocation(m_id, i, attribs[i].c_str());
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

                asl::for_each_arg([] (auto& shader)
                {
                    auto sid = shader.getID();
                    glDeleteShader(sid);
                }, std::forward<Shaders>(pack)...);

                TEWI_EXPECTS(0, "Shader failed to link");
            }

            asl::for_each_arg([this] (auto& shader)
            {
                auto sid = shader.getID();
                glDetachShader(m_id, sid);
                glDeleteShader(sid);
            }, std::forward<Shaders>(pack)...);
        }


        template <typename Container,
                 typename... Shaders>
        ShaderProgram(const Container& attribs, Shaders&&... pack)
            : m_id(glCreateProgram())
            , m_attribNum(0)
        {
            asl::for_each_arg([this] (auto& shader)
            {
                auto sid = shader.getID();
                glAttachShader(m_id, sid);
            }, std::forward<Shaders>(pack)...);

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

                asl::for_each_arg([] (auto& shader)
                {
                    auto sid = shader.getID();
                    glDeleteShader(sid);
                }, std::forward<Shaders>(pack)...);

                TEWI_EXPECTS(0, "Shader failed to link");
            }

            asl::for_each_arg([this] (auto& shader)
            {
                auto sid = shader.getID();
                glDetachShader(m_id, sid);
                glDeleteShader(sid);
            }, std::forward<Shaders>(pack)...);
        }

        ShaderProgram(const ShaderProgram&) = default;
        ShaderProgram(ShaderProgram&&) = default;

        ShaderProgram& operator=(const ShaderProgram&) = default;
        ShaderProgram& operator=(ShaderProgram&&) = default;

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

        template <typename Container,
                 std::enable_if_t<
                     !std::is_same<
                        typename Container::value_type, const char*>::value,
                 bool> = false>
        std::vector<asl::mut_u32> getUniformLocation(const Container& uniformName)
        {
            std::vector<asl::mut_u32> arr(uniformName.size());

            for (int i = 0; i < uniformName.size(); ++i)
            {
                asl::u32 location = glGetUniformLocation(m_id, uniformName[i]);
                TEWI_EXPECTS(location != GL_INVALID_INDEX, "Invalid uniform variable " + std::to_string(uniformName[i]));
                arr.push_back(location);
            }

            return arr;
        }

        template <asl::sizei N>
        std::array<asl::u32, N> getUniformLocation(const std::array<const char*, N>& uniformName)
        {
            std::array<asl::u32, N> arr;

            for (int i = 0; i < N; ++i)
            {
                asl::u32 location = glGetUniformLocation(m_id, uniformName[i]);
                TEWI_EXPECTS(location != GL_INVALID_INDEX, "Invalid uniform variable " + std::to_string(uniformName[i]));
                arr[i] = (location);
            }

            return arr;
        }


        template <asl::sizei N, typename StringType>
        std::array<asl::u32, N> getUniformLocation(const std::array<StringType, N>& uniformName)
        {
            std::array<asl::u32, N> arr;

            for (int i = 0; i < N; ++i)
            {
                asl::u32 location = glGetUniformLocation(m_id, uniformName[i].c_str());
                TEWI_EXPECTS(location != GL_INVALID_INDEX, "Invalid uniform variable " + std::to_string(uniformName[i].c_str()));
                arr[i] = (location);
            }

            return arr;
        }


    private:
        asl::u32 m_id;
        asl::mut_sizei m_attribNum;
    };

    template <template <typename> class ShaderTypePolicy,
             template <typename> class ShaderFindPolicy>
    class TEWI_EXPORT Shader<API::OpenGLTag, ShaderTypePolicy, ShaderFindPolicy> final
        : private ShaderTypePolicy<API::OpenGLTag>
        , private ShaderFindPolicy<ShaderTypePolicy<API::OpenGLTag>>
    {
    public:
        using STypeImpl = ShaderTypePolicy<API::OpenGLTag>;
        using SFindImpl = ShaderFindPolicy<STypeImpl>;
        using api_type = API::OpenGLTag;

        explicit Shader(API::Device<API::OpenGLTag>&, const char* path)
            : m_id(STypeImpl::create())
        {
            STypeImpl::compile(SFindImpl::getShader(path), m_id);
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
    };
} // namespace tewi
