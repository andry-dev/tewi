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
		auto compile(const std::string& path, asl::u32) { return 0; }
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
	

	/** \brief A shader
	 *
	 * Requires the number of the API that you want to use
	 *
	 *
	 * \note
	 * Different graphics APIs requries different extensions for the
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
	template <typename APINum,
			 template <typename> class ShaderTypePolicy,
			 template <class> class ShaderFindPolicy = SubstitutionFindPolicy>
	class Shader
		: private ShaderTypePolicy<APINum>
		, private ShaderFindPolicy<ShaderTypePolicy<APINum>>
	{
	public:
		using ShaderTypeImpl = ShaderTypePolicy<APINum>;
		using ShaderFindImpl = ShaderFindPolicy<ShaderTypePolicy<APINum>>;

		explicit Shader(API::Device<APINum>& dev, const char* path)
			: m_path(ShaderFindImpl::getShaderPath(path))
			, m_id(ShaderTypeImpl::create())
		{
			ShaderTypeImpl::compile(m_path, m_id);
		}

		using api_num = APINum;

	private:
		asl::u32 m_id;
		const char* m_path;
	};

	template <typename APINum>
	class ShaderProgram
	{
	public:
		void enable() { }

		void disable() { }

		void addAttrib() { }

		template <asl::sizei N>
		void addAttrib(const std::array<const char*, N>& args) { }

		asl::u32 getUniformLocation(const std::string& uniformName) { return 0; }

		template <unsigned long N>
		std::array<asl::u32, N> getUniformLocation(const std::array<const char*, N>& uniformName) { }

	private:
		asl::u32 m_id;
		asl::mut_sizei m_attribNums;
	};

	template <typename... Shaders>
	using ShaderPack = std::tuple<Shaders...>;

	template <typename... Shaders>
	constexpr inline ShaderPack<Shaders...> make_shader_pack(Shaders... s)
	{
		return { std::forward<Shaders>(s)... };
	}

	namespace detail
	{
		template <typename S, typename... Rest>
		struct get_api
		{
			using value = typename std::decay_t<S>::api_num;
		};

	} // namespace detail

	template <typename... Shaders, typename APINum = typename detail::get_api<Shaders...>::value>
	inline ShaderProgram<APINum> make_shader_program(ShaderPack<Shaders...> pack)
	{
		return {  };
	}
}
