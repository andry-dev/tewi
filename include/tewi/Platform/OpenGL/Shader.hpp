#pragma once

#include <utility>
#include <fstream>
#include <cstdio>
#include <string>
#include <vector>

#include "GL/glew.h"

#include "tewi/Common.h"

#include "tewi/IO/BasicIO.h"
#include "tewi/Video/Shader.hpp"
#include "tewi/Video/API/API.h"
#include "tewi/Utils/Log.h"

#include "asl/functional"


namespace tewi
{
    inline TEWI_EXPORT void compileGLSL(asl::string_view shadertext, asl::u32 id)
    {
        auto str_ptr = shadertext.data();

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

        void compile(asl::string_view shadertext, asl::u32 id)
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

        void compile(asl::string_view path, asl::u32 id)
        {
            compileGLSL(path, id);
        }
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

        explicit Shader(const API::Device<API::OpenGLTag>&, asl::string_view path)
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

    template <>
    class TEWI_EXPORT ShaderProgram<API::OpenGLTag>
    {
    public:
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
                glBindAttribLocation(m_id, i, attribs[i].data());
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

        asl::u32 getUniformLocation(asl::string_view uniformName)
        {
            asl::u32 location = glGetUniformLocation(m_id, uniformName.data());
            TEWI_EXPECTS(location != GL_INVALID_INDEX,
                         "Invalid uniform variable \"" + asl::to_string(uniformName) + "\"");
            return location;
        }

        template <asl::sizei N>
        std::array<asl::u32, N> getUniformLocation(const std::array<asl::string_view, N>& uniformName)
        {
            std::array<asl::u32, N> arr;

            for (int i = 0; i < N; ++i)
            {
                asl::u32 location = glGetUniformLocation(m_id, uniformName[i]);
                TEWI_EXPECTS(location != GL_INVALID_INDEX,
                             "Invalid uniform variable " + std::to_string(uniformName[i]));
                arr[i] = (location);
            }

            return arr;
        }

        template <typename Container,
                     std::enable_if_t<
                         !std::is_same<Container, asl::string_view>::value
                     >
                 >
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

    private:
        asl::u32 m_id;
        asl::mut_sizei m_attribNum;
    };


    template <>
    auto translateVertexLayoutType<API::OpenGLTag>(VertexLayout::Types type)
    {
        switch (type)
        {
        case VertexLayout::Types::Float32: return GL_FLOAT;
        case VertexLayout::Types::Float64: return GL_DOUBLE;
        case VertexLayout::Types::UInt8: return GL_UNSIGNED_BYTE;
        case VertexLayout::Types::Int8: return GL_BYTE;
        case VertexLayout::Types::UInt16: return GL_UNSIGNED_SHORT;
        case VertexLayout::Types::Int16: return GL_SHORT;
        case VertexLayout::Types::UInt32: return GL_UNSIGNED_INT;
        case VertexLayout::Types::Int32: return GL_INT;
        };
    }
} // namespace tewi
