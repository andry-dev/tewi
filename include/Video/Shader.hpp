#pragma once

#include <array>
#include <string>

#include "Common.h"
#include "asl/types"
#include "gsl/string_span"

#include "IO/BasicIO.h"

#include "Video/API/Device.hpp"

#include "Common.h"

namespace tewi
{

    template <typename APIType>
    class TEWI_EXPORT VertexShader
    {
    public:
        using api_type = APIType;
        using interface_only = void;

    protected:
        auto create();
        auto compile();
    };

    template <typename APIType>
    class TEWI_EXPORT FragmentShader
    {
    public:
        using api_type = APIType;
        using interface_only = void;

    protected:
        auto create();
        auto compile();
    };

    template <typename AnyShader>
    class TEWI_EXPORT ShaderFromMemoryPolicy
    {
    public:
        using interface_only = void;
    protected:
        std::string getShader(gsl::string_span loc)
        {
            return loc;
        }
    };

    template <typename AnyShader>
    class TEWI_EXPORT SubstitutionFindPolicy
    {
    public:
        using interface_only = void;
    protected:
        std::string getShader(gsl::string_span) const;
    };

    template <typename APIType>
    class TEWI_EXPORT SubstitutionFindPolicy<VertexShader<APIType>>
    {
    protected:
        std::string getShader(gsl::string_span path) const
        {
            const auto finalPath = IO::findCorrectFile(path, shaderExts).second;
            return IO::readFileContents(finalPath);
        }

        const std::array<const char*, 2> shaderExts =
        {{
            ".vert",
            ".glsl.vert"
        }};

        const std::array<const char*, 1> shaderNames =
        {{
            "vert"
        }};
    };

    template <typename APIType>
    class TEWI_EXPORT SubstitutionFindPolicy<FragmentShader<APIType>>
    {
    protected:
        std::string getShader(gsl::string_span path) const
        {
            const auto finalPath = IO::findCorrectFile(path, shaderExts).second;
            return IO::readFileContents(finalPath);
        }

        const std::array<const char*, 2> shaderExts = { {
            ".frag",
            ".glsl.frag"
        } };

        const std::array<const char*, 1> shaderNames = { {
            "frag"
        } };
    };

    /** \brief A shader, either vertex, fragment, compute or an user-defined one.
     *
     *
     * \tparam APIType The API that you want to use.
     * \tparam ShaderTypePolicy The type of shader that you want to instantiate,
     * this can be either a VertexShader, FragmentShader or a custom struct. See
     * VertexShader for the interface.
     * \tparam ShaderFindPolicy How we want to find the shader path, by default it
     * tries to automatically deduce the extension
     *
     * \note
     * Different graphics APIs requires different extensions for the
     * various shaders.
     * For example, OpenGL requires a GLSL source, while Vulkan requires a
     * pre-compiled SPIR-V binary.
     * \par
     * If you pass a path without an extension (ie: "shaders/test"), then
     * we try to load the file with the appropriate extension appended;
     * if we can't find the file then we error out.
     * \par
     * If you pass an extension and it is wrong (ie: "shaders/test.spirv"
     * instead of an OpenGL shader), then we substitute the extension
     * with the one we are looking for and see if we can find the file; if
     * we can't then we error out.
     * \par
     * We do all of this because of API compatibility.
     */
    template <typename APIType,
             template <class> class ShaderTypePolicy,
             template <class> class ShaderFindPolicy = SubstitutionFindPolicy>
    class TEWI_EXPORT Shader final
        : private ShaderTypePolicy<APIType>
        , private ShaderFindPolicy<ShaderTypePolicy<APIType>>
    {
    public:
        using STypeImpl = ShaderTypePolicy<APIType>;
        using SFindImpl = ShaderFindPolicy<STypeImpl>;

        explicit Shader(const API::Device<APIType>& dev, const std::string& path)
            : m_id(STypeImpl::create())
        {
            STypeImpl::compile(SFindImpl::getShader(path), m_id);
        }

        using api_type = APIType;

    private:
        asl::u32 m_id;
    };

    namespace detail
    {
        template <typename S, typename... Rest>
        struct TEWI_EXPORT get_api
        {
            using value = typename std::decay_t<S>::api_type;
            static_assert(is_api_compatible_v<S, Rest...>,
                    "You're mixing incompatible API tags");
        };
    } // namespace detail

    template <typename... Shaders>
    using ShaderPack = std::tuple<Shaders...>;

    /** Creates a ShaderPack out of some shaders.
     *
     */
    template <typename... Shaders>
    constexpr inline TEWI_EXPORT ShaderPack<Shaders...> make_shader_pack(Shaders&&... s)
    {
        return { std::forward<Shaders>(s)... };
    }

    /** \brief A shader program
     *
     * The shader program is the final "shader executable", where we link all
     * the other shaders together.
     * This is the class you use to manipulate shaders, like adding attributes
     * or retrieving uniforms.
     *
     * \tparam APIType The type of the API you want.
     *
     */
    template <typename APIType>
    class TEWI_EXPORT ShaderProgram
    {
    public:
        using api_type = APIType;
        using interface_only = void;

        template <typename Container, typename... Shaders>
        ShaderProgram(const Container& attribs, Shaders&&... s);

        ShaderProgram(const ShaderProgram&) = default;
        ShaderProgram(ShaderProgram&&) = default;

        ShaderProgram& operator=(const ShaderProgram&) = default;
        ShaderProgram& operator=(ShaderProgram&&) = default;

        /** Enables the shader.
         *
         */
        void enable();

        /** Disables the shader.
         *
         */
        void disable();

        /** Returns the index of an uniform.
         *
         */
        asl::u32 getUniformLocation(gsl::string_span uniformName);

        /** Returns an array of indices of various uniforms.
         *
         */
        template <asl::sizei N>
        std::array<asl::u32, N> getUniformLocation(const std::array<gsl::string_span, N>& uniformName);

        /** Returns an array of indices of various uniforms.
         *
         */
        template <typename Container,
                     std::enable_if_t<
                         !std::is_same<Container, gsl::string_span>::value
                     >
                 >
        std::vector<asl::mut_u32> getUniformLocation(const Container& uniformName);


    private:
        asl::u32 m_id;
        asl::mut_sizei m_attribNums;
    };


    /** Creates a ShaderProgram out of some shaders; basically it allows to skip
     * the intermediate ShaderPack creation.
     *
     */
    template <typename Container, typename... Shaders, typename APINum = typename detail::get_api<Shaders...>::value>
    constexpr inline TEWI_EXPORT ShaderProgram<APINum> make_shader_program(const Container& attribs, Shaders&&... pack)
    {
        return { attribs, std::forward<Shaders>(pack)... };
    }

    /** \example shader_creation.cpp
     *
     * Shows how to create a shader program.
     */
}

#include "Platform/OpenGL/Shader.hpp"
#include "Platform/Vulkan/Shader.hpp"
#include "Platform/NullRenderer/Shader.hpp"
