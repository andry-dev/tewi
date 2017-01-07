#pragma once

#include <array>
#include <string>

#include "Common.h"
#include "Utils/Types.h"

namespace tewi
{
	namespace API
	{
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
		template <int APINum>
		class Shader
		{
		public:
			/** Constructor
			 *
			 * Please, implement it with std::move if you store them
			 */
			Shader(const std::string& vertPath, const std::string& fragPath)
			{
			}

			void addAttrib(const std::string& attrib) {  }
			void addAttrib(const std::initializer_list<std::string>& args) {  }

			// TODO: Maybe we can exploit operator[]? 06-01-2017
			u32 getUniformLocation(const std::string& uniformName) { return -1; }

			template <unsigned long N>
			std::array<u32, N> getUniformLocation(const std::array<const char*, N>& uniformsName) { return  { { -1 } };  }
			
			// TODO: Do I really need this?
			void link() {  }

			void enable() {  }
			void disable() {  }
		};
	}
}
