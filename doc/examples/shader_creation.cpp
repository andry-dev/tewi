#include "Video/Shader.hpp"
#include "Video/API/API.hpp"

using namespace tewi;
using namespace tewi::API;

// Easiest example
void simple_creation()
{
	// Create the shaders first
	Shader<OpenGLTag, VertexShader> vert("path/to/shader");
	Shader<OpenGLTag, FragmentShader> frag("path/to/shader");

	// Then we create the program by passing the attributes and the shaders
	
	// You can use any other container that has operator[] and any type that
	// implements the function "c_str()"
	const std::array<const char*, 2> attribs =
	{{
		"vertexPos",
		"vertexCol"
	}};

	// You can also create the container in-line with the brace initialization
	// syntax
	ShaderProgram<OpenGLTag> program(attribs, vert, frag);

	// OR:
	// auto program = make_shader_program(attribs, vert, frag);

	// Enables the program
	program.enable();

	// Disables it
	program.disable();
}

// But we don't really need Shader in memory
void deallocation()
{
	// Manual new and delete to prove a point, don't kill me
	auto* vertPtr = new Shader<OpenGLTag, VertexShader>("path/to/shader");
	auto* fragPtr = new Shader<OpenGLTag, FragmentShader>("path/to/shader");

	auto program = make_shader_program(/* attribs */, *vertPtr, *fragPtr);

	delete vertPtr;
	delete fragPtr;

	program.enable();

	// It sill works even if we delete the shaders

	program.disable();

	/* This works because the Shader class is not needed to create the final
	 * program (that you would manipulate) but it just represents the shader
	 * file. For example in OpenGL it just compiles the shader, it doesn't link
	 * it.
	 *
	 * The constructor of ShaderProgram takes all the shaders, links them and
	 * keeps only the final program, not the single shaders; this should not use
	 * much resources.
	 *
	 * tl;dr: ShaderProgram doesn't owns any Shader, it just uses them to
	 * compile the final program.
	 *
	 */
}

// So, how can I write my own shader?

// Default implementation, not API specific
template <typename APIType> // Required
struct MyShader
{
protected:
	auto create() { return 0; }
	auto compile() { return 0; }
};

// OpenGL specific implementation
template <>
struct MyShader<OpenGLTag>
{
protected:
	auto create()
	{
		// whatever
	}

	void compile(const std::string& path, asl::u32 id)
	{
		// ...
	}
};

template <>
struct MyShader<VulkanTag>
{
protected:
	auto create()
	{
		// ...
	}

	void compile()
	{
		// ...
	}
};


struct MetalTag {  };

// Yes, you can (and should) also do this if you created your own API.
// And you can create your own variables and functions, Shader only need
// create() and compile().
//
// You can even change the parameters for the functions if you specialized
// Shader with your API; it's all yours.
template <>
struct MyShader<MetalTag>
{
protected:
	auto create()
	{

	}

	auto compile()
	{

	}
private:
	int myVar = 0;
};


void use_my_shader()
{
	Shader<OpenGLTag, MyShader> sh("path/to/shader");

	auto program = make_shader_program(/* attribs */, sh);

	// You should know the gist.
}

// If you want to find the exact path without modifications you just create another
// policy:

// Here you can specialize for the shader policy itself, not the API, so you can
// do specific stuff on specific shaders or APIs
template <typename AnyShader>
class ExactFindPolicy
{
protected:
	IO::Path getShaderPath(const std::string& path) const
	{
		return { true, path };
	}
};

void exact_filename()
{
	Shader<OpenGLTag, VertexShader, ExactFindPolicy> sh("path/to/file.vert");

	// ...
}

// "I don't want to write all of that"

namespace my_namespace
{
	template <typename APIType>
	using VertShader = tewi::Shader<APIType, tewi::VertexShader>;


	void foo()
	{
		VertShader<OpenGLTag> sh("path/to/shader");

		// ...
	}
}
