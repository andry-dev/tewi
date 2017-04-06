#pragma once

#include <array>
#include <string>

#include "Common.h"
#include "asl/types"

#include "IO/BasicIO.h"

#include "Video/API/Device.hpp"

namespace tewi
{
	template <typename APIType>
	class VertexShader
	{
	protected:
		auto create() { return 0; }
		auto compile() { return 0; }
	};

	template <typename APIType>
	class FragmentShader
	{
	protected:
		auto create() { return 0; }
		auto compile() { return 0; }
	};

	template <typename AnyShader>
	class SubstitutionFindPolicy
	{
	protected:
		IO::Path getShaderPath(const std::string&) const
		{
			return { false, "" };
		}
	};

	template <typename APIType>
	class SubstitutionFindPolicy<VertexShader<APIType>>
	{
	protected:
		IO::Path getShaderPath(const std::string& path) const
		{
			return IO::findCorrectFile(path, shaderExts);
		}

		const std::array<const char*, 2> shaderExts = { {
			".vert",
			".glsl.vert"
		} };

		const std::array<const char*, 1> shaderNames = { {
			"vert"
		} };
	};

	template <typename APIType>
	class SubstitutionFindPolicy<FragmentShader<APIType>>
	{
	protected:
		IO::Path getShaderPath(const std::string& path) const
		{
			return IO::findCorrectFile(path, shaderExts, shaderNames);
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
			 template <typename> class ShaderTypePolicy,
			 template <class> class ShaderFindPolicy = SubstitutionFindPolicy>
	class Shader final
		: private ShaderTypePolicy<APIType>
		, private ShaderFindPolicy<ShaderTypePolicy<APIType>>
	{
	public:
		using ShaderTypeImpl = ShaderTypePolicy<APIType>;
		using ShaderFindImpl = ShaderFindPolicy<ShaderTypePolicy<APIType>>;

		explicit Shader(API::Device<APIType>& dev, const char* path)
			: m_path(ShaderFindImpl::getShaderPath(path))
			, m_id(ShaderTypeImpl::create())
		{
			ShaderTypeImpl::compile(m_path, m_id);
		}

		using api_num = APIType;

	private:
		asl::u32 m_id;
		const char* m_path;
	};

	namespace detail
	{
		template <typename S, typename... Rest>
		struct get_api
		{
			using value = typename std::decay_t<S>::api_num;
		};
	} // namespace detail

	template <typename... Shaders>
	using ShaderPack = std::tuple<Shaders...>;

	/** Creates a ShaderPack out of some shaders.
	 *
	 */
	template <typename... Shaders>
	constexpr inline ShaderPack<Shaders...> make_shader_pack(Shaders&&... s)
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
	class ShaderProgram
	{
	public:
		template <asl::sizei N, typename... Shaders>
		ShaderProgram(const std::array<const char*, N> attribs, ShaderPack<Shaders...>& s) {  }

		/** Enables the shader.
		 *
		 */
		void enable() { }

		/** Disables the shader.
		 *
		 */
		void disable() { }

		/** Returns the index of an uniform.
		 *
		 */
		asl::u32 getUniformLocation(const std::string& uniformName) { return 0; }

		/** Returns an array of indices of various uniforms.
		 *
		 */
		template <asl::sizei N>
		std::array<asl::u32, N> getUniformLocation(const std::array<const char*, N>& uniformName) { }

	private:
		asl::u32 m_id;
		asl::mut_sizei m_attribNums;
	};


	/** Creates a ShaderProgram out of some shaders; basically it allows to skip
	 * the intermediate ShaderPack creation.
	 *
	 */
	template <asl::sizei N, typename... Shaders, typename APINum = typename detail::get_api<Shaders...>::value>
	constexpr inline ShaderProgram<APINum> make_shader_program(const std::array<const char*, N>& attribs, Shaders... pack)
	{
		return { attribs, make_shader_pack(pack...) };
	}

	/** \example shader_creation.cpp
	 *
	 * Shows how to create a shader program.
	 */
}


#include "Platform/OpenGL/Shader.hpp"
#include "Platform/Vulkan/Shader.hpp"
