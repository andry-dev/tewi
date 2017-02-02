#pragma once

#include "Video/API/API.h"

#include "Video/API/Shader.hpp"

#include "IO/BasicIO.h"

namespace tewi
{
	namespace API
	{
		template <>
		class VertexShader<API_TYPE::VULKAN>
		{
		protected:
			auto create(const std::string& path)
			{
				return IO::fileToBuffer<char>(path);
			}

			void compile()
			{

			}
		};

		template <>
		class FragmentShader<API_TYPE::VULKAN>
		{
		protected:
			auto create(const std::string& path)
			{
				return IO::fileToBuffer<char>(path);
			}

			void compile()
			{
			}
		};

		template <>
		class ShaderProgram<API_TYPE::VULKAN>
		{

		};

		template <template <num> class ShaderTypePolicy,
				 template <typename> class ShaderFindPolicy>
		class Shader<API_TYPE::VULKAN, ShaderTypePolicy, ShaderFindPolicy>
			: private ShaderTypePolicy<API_TYPE::VULKAN>
			, private ShaderFindPolicy<ShaderTypePolicy<API_TYPE::VULKAN>>
		{
		public:
			using ShaderTypeImpl = ShaderTypePolicy<API_TYPE::VULKAN>;
			using ShaderFindImpl = ShaderFindPolicy<ShaderTypeImpl>;

			explicit Shader(const std::string& path)
				: m_path(ShaderFindImpl::getShaderPath(path))
			{
				
			}

			~Shader() = default;
		
			Shader(const Shader& rhs) = default;
			Shader& operator=(const Shader& rhs) = default;
		
			Shader(Shader&& rhs) = default;
			Shader& operator=(Shader&& rhs) = default;

		private:
			std::string m_path;
		};
	} // namespace API
} // namespace tewi
