#pragma once

#include <array>
#include <string>

#include "Common.h"
#include "Utils/Types.h"

#include "IO/BasicIO.h"

namespace tewi
{
	namespace API
	{
		template <num APINum>
		class VertexShader
		{
		protected:
			auto create() { return 0; }
			auto compile() { return 0; }
		};

		template <num APINum>
		class FragmentShader
		{
		protected:
			auto create() { return 0; }
			auto compile(const std::string& path, u32) { return 0; }
		};

		template <template <num> class AnyShader>
		class SubstitutionFindPolicy
		{
		protected:
			IO::Path getShaderPath(const std::string&) const
			{
				return { false, "" };
			}
		};

		template <>
		class SubstitutionFindPolicy<VertexShader>
		{
		protected:
			IO::Path getShaderPath(const std::string& path) const
			{
				return IO::findCorrectFile(path, shaderExts);
			}

			static constexpr std::array<const char*, 2> shaderExts = { {
				".vert",
				".glsl.vert"
			} };

			static constexpr std::array<const char*, 1> shaderNames = { {
				"vert"
			} };
		};

		template <>
		class SubstitutionFindPolicy<FragmentShader>
		{
		protected:
			IO::Path getShaderPath(const std::string& path) const
			{
				return IO::findCorrectFile(path, shaderExts, shaderNames);
			}

			static constexpr std::array<const char*, 2> shaderExts = { {
				".frag",
				".glsl.frag"
			} };

			static constexpr std::array<const char*, 1> shaderNames = { {
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
		template <num APINum,
				 template <num> class ShaderTypePolicy,
				 template <class> class ShaderFindPolicy = SubstitutionFindPolicy>
		class Shader
			: private ShaderTypePolicy<APINum>
			, private ShaderFindPolicy<ShaderTypePolicy<APINum>>
		{
		public:
			using ShaderTypeImpl = ShaderTypePolicy<APINum>;
			using ShaderFindImpl = ShaderFindPolicy<ShaderTypePolicy<APINum>>;

			explicit Shader(const char* path)
				: m_path(ShaderFindImpl::getShaderPath(path))
				, m_id(ShaderTypeImpl::create())
			{
				ShaderTypeImpl::compile(m_path, m_id);
			}

			constexpr static sizei api_num = APINum;

		private:
			u32 m_id;
			const char* m_path;
		};

		template <num APINum>
		class ShaderProgram
		{
		public:
			void enable() { }

			void disable() { }

			void addAttrib() { }

			template <unsigned long N>
			void addAttrib(const std::array<const char*, N>& args) { }

			u32 getUniformLocation(const std::string& uniformName) { return 0; }

			template <unsigned long N>
			std::array<u32, N> getUniformLocation(const std::array<const char*, N>& uniformName) { }

		private:
			u32 m_id;
			mut_sizei m_attribNums;
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
			template <typename... Shaders>
			struct get_api
			{
				static constexpr num value = get_api<Shaders...>::value;
			};

			template <typename S, typename... Rest>
			struct get_api<S, Rest...>
			{
				static constexpr num value = std::decay_t<S>::api_num;
			};

		} // namespace detail

		template <typename... Shaders, num APINum = detail::get_api<Shaders...>::value>
		inline ShaderProgram<APINum> make_shader_program(ShaderPack<Shaders...> pack)
		{
			ShaderProgram<APINum> p = {  };
			return p;
		}
	}
}
