# Tewi

Wannabe extensible, easy to use and somewhat fast engine.

Alpha-grade software, API may change and I need to refactor some horrible code.

Examples can be found in `doc/examples`.

## Feature list

 * Support for OpenGL and (possibly) other APIs
 * Can draw 2D things on the screen in OpenGL-mode

## Scope of the project

I want to remark that this is an _experimental toy project_, I don't think anyone would use it except for me.
The API is not friendly enough and it poses several problems (long compile-times for example).
Nonetheless, the intended scope is to create a (mostly) header-only framework that can be integrated in any project to create basic games or physics simulations. I also want to support different graphics APIs (even terminal and software rendering), different rendering backends ("simple", batch, deferred, etc...) and modes (2D, 3D, "2.5D").

But honestly, at the end of the day I'm just experimenting with C++14 and CMake.

## Why should I even use this library?

You may choose to use this if:

 * You want to painlessly include a drawing framework in your project
 * You despise OOP concepts such as inheritance, runtime polymorphism, etc...
 * You don't like exceptions
 * You want to code something quickly for many APIs and OSes
 * You optionally want to change _anything_ about _any_ implementation
 * You are a masochist

You may choose **not** to use this if:

 * You want mature and stable frameworks
 * You want a sane API
 * You _really_ like OOP as done in Java
 * You think templates make an API unnecessary convoluted

## Design choices

This library avoids inheritance and `virtual` by using templates.
It tries to delegate most runtime decisions to compile-time via policy classes, concepts, occasional CRTP and template specialization abuse.
While it's not a compiler turture test (like Boost is), it's still not easy on the compiler.

While you _can_ compile the library as a dynamic library I advise you to _not_ do it because it can get in the way of LTO and, generally speaking, there is no reason to use dynamic linking.

## Dependencies

Required runtime:

 * GLEW (only for Linux)

Resolved by git submodules:

 * [asl](https://github.com/andry-dev/asl)
 * [GLFW](https://github.com/glfw/glfw)
 * [glm](https://github.com/g-truc/glm)
 * [stb](https://github.com/nothings/stb)
 * [Catch](https://github.com/philsquared/Catch)

## TODO / Broken stuff

Strict engine stuff:

 * [x] Finish the Vulkan port so I can fix bugs (See [reisen](https://github.com/andry-dev/reisen))
 * [x] Implement GLFW mouse support (again)
 * [ ] Implement basic 2D stuff (like rotations)
 * [ ] Basic event system
 * [ ] Basic sound system
 * [ ] GUI (probably a wrapper around [nuklear](https://github.com/vurtun/nuklear))
 * [ ] Particle system
 * [ ] VFS
 * [ ] 3D (?)
 * [ ] Optimizations (cache, algorithms, multi-threading, etc...)
 * [ ] Code cleanup

Addons:

 * [ ] Serialization module and custom binary reader
 * [ ] Network module (probably a wrapper around enet)
 * [ ] Mod loading? (LUA?)

Strict C++:

 * [ ] Concepts
 * [ ] Modules
 * [ ] Actually write decent tests

Strict CMake:

 * [ ] Ditch GLEW in favor of a git submodule-compatible library
 * [ ] Split up everything into various modules?

Project:

 * [ ] Enable the use of other build systems (build2, conan, etc...)
 * [ ] Choose a license (probably BSD, MPL or MIT)
