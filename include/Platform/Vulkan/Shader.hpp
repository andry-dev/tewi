#pragma once

#include "Video/API/API.h"

#include "Video/API/Shader.hpp"

#include "IO/BasicIO.h"

namespace tewi
{
	namespace API
	{
		namespace
		{
			const std::array<const char*, 1> g_shaderExts = { {
				".spirv"
			} };
		}

		template <>
		class Shader<API_TYPE::VULKAN>
		{
		public:
			Shader(const std::string& vertPath, const std::string& fragPath)
				: m_vertPath(IO::findCorrectFile(vertPath, g_shaderExts))
				, m_fragPath(IO::findCorrectFile(fragPath, g_shaderExts))
			{
				
			}
			~Shader() = default;
		
			Shader(const Shader& rhs) = default;
			Shader& operator=(const Shader& rhs) = default;
		
			Shader(Shader&& rhs) = default;
			Shader& operator=(Shader&& rhs) = default;

		private:
			
			std::string m_vertPath;
			std::string m_fragPath;
		};
	} // namespace API
} // namespace tewi
