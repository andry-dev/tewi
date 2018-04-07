tewi is an experimental 2D and 3D game "engine" written in C++14.

## What it is

* A framework that assists a developer in the creation of a game in C++.
* A toy project.

## What it is not

* An application like Unity that can create a game graphically.
* Your go-to framework for making games.

## Goal

The goal was to create a fast and extensible engine that supports multiple
graphics APIs without the use of inheritance or the likes. The interface tries
to stay relatively generic (via templates and the likes).

## Supported graphics APIs

* OpenGL 4+
* Null renderer (dun)
* <span class="strike">Software rendering</span> (planned)
* <span class="strike">Terminal rendering</span> (planned)
* <span class="strike">Vulkan</span> (see [reisen](https://github.com/andry-dev/reisen))
* <span class="strike">DirectX</span> (planned)

## Dependencies

* GLEW (headers and runtime, **required**)
* [GLFW](https://github.com/glfw/glfw) (git submodule)
* [asl](https://github.com/andry-dev/asl) (git submodule)
* [glm](https://github.com/g-truc/glm) (git submodule)
* [stb](https://github.com/nothings/stb) (git submodule)
* [Catch](https://github.com/philsquared/Catch) (git submodule, used for tests)
* Doxygen (soft build-time dependency, **not required**)
* clang-tidy (soft build-time dependency, **not required**)
* A standard conforming C++14 compiler (VS 2017+, GCC 6.2+, clang 4+).

## CMake build options

* If `TEWI_BUILD_TESTS` is `ON` then CMake will enable tests with Catch.
* If `BUILD_SHARED_LIBS` is `ON` then tewi will be built as a dynamic library.
