#include "GL/glew.h"

#include "tewi/Common.h"

#include "tewi/Video/Shader.hpp"
#include "tewi/Video/API/API.h"
#include "tewi/Utils/Log.h"

namespace tewi
{
    inline TEWI_EXPORT void compileGLSL(asl::string_view shadertext, asl::u32 id)
    {
        auto str_ptr = shadertext.data();

        glShaderSource(id, 1, &str_ptr, nullptr);
        glCompileShader(id);

        asl::num res = 0;
        glGetShaderiv(id, GL_COMPILE_STATUS, &res);

        if (res == GL_FALSE)
        {
            asl::num maxLen = 0;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLen);

            std::vector<GLchar> errorLog(maxLen);

            glGetShaderInfoLog(id, maxLen, &maxLen, errorLog.data());
            Log::warning(errorLog.data());
            TEWI_EXPECTS(false, "Shader failed to compile");
        }
    }

    ShaderProgram<API::OpenGLTag>::ShaderProgram(
            gsl::span<const ShaderDescription> shaderDescriptions,
            gsl::span<const asl::string_view> attributes)
        : m_id(glCreateProgram())
        , m_attributeNum(attributes.size())
    {
        TEWI_EXPECTS(m_id != 0, "Shader Program not correctly created");

        const auto maxShaders = shaderDescriptions.size();

        std::vector<asl::u32> shaderIDs(maxShaders);

        // Compile all shaders
        for (asl::u32 i = 0; i < maxShaders; ++i)
        {
            switch (shaderDescriptions[i].type)
            {
            case ShaderType::Vertex:
                shaderIDs[i] = glCreateShader(GL_VERTEX_SHADER);
                TEWI_EXPECTS(shaderIDs[i] != 0, "Can't create vertex shader");
                break;

            case ShaderType::Fragment:
                shaderIDs[i] = glCreateShader(GL_FRAGMENT_SHADER);
                TEWI_EXPECTS(shaderIDs[i] != 0, "Can't create fragment shader");
                break;

            default:
                TEWI_EXPECTS(false, "Not implemented yet :(");
            }

            compileGLSL(shaderDescriptions[i].sourceCode, shaderIDs[i]);

            glAttachShader(m_id, shaderIDs[i]);
        }

        for (asl::u32 i = 0; i < attributes.size(); ++i)
        {
            glBindAttribLocation(m_id, i, attributes[i].data());
        }

        glLinkProgram(m_id);

        {
            asl::num res = 0;
            glGetProgramiv(m_id, GL_LINK_STATUS, &res);

            if (res == GL_FALSE)
            {
                int maxLen = 0;
                glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &maxLen);

                std::vector<GLchar> errorLog(maxLen);

                glGetProgramInfoLog(m_id, maxLen, &maxLen, &errorLog[0]);

                Log::warning(errorLog.data());

                glDeleteProgram(m_id);

                for (auto shid : shaderIDs)
                {
                    glDetachShader(m_id, shid);
                    glDeleteShader(shid);
                }

                TEWI_EXPECTS(false, "Shader failed to link");
            }
        }

        for (auto shid : shaderIDs)
        {
            glDetachShader(m_id, shid);
            glDeleteShader(shid);
        }

        TEWI_ENSURES(m_id != 0, "Shader Program ID reset! THIS IS A BUG");
        TEWI_ENSURES(m_attributeNum == attributes.size(), "Something Something");
    }

    ShaderProgram<API::OpenGLTag>::~ShaderProgram()
    {
        glDeleteProgram(m_id);
    }

    void ShaderProgram<API::OpenGLTag>::enable()
    {
        glUseProgram(m_id);
        for (asl::sizei i = 0; i < m_attributeNum; ++i)
        {
            glEnableVertexAttribArray(i);
        }
    }

    void ShaderProgram<API::OpenGLTag>::disable()
    {
        for (asl::sizei i = 0; i < m_attributeNum; ++i)
        {
            glDisableVertexAttribArray(i);
        }
        glUseProgram(0);
    }

    asl::i32 ShaderProgram<API::OpenGLTag>::getUniformLocation(asl::string_view str)
    {
        return glGetUniformLocation(m_id, str.data());
    }

    void ShaderProgram<API::OpenGLTag>::setUniform(asl::i32 uniform, const glm::mat4& mat)
    {
        glUniformMatrix4fv(uniform, 1, GL_FALSE, &mat[0][0]);
    }

    auto translateVertexLayoutType(API::OpenGLTag, VertexLayout::Types type)
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

        return -1;
    }
} // namespace tewi
