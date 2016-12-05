# Tewi
---

Wannabe extensible, easy to use and somewhat fast engine.

Alpha-grade software, API may change and I need to refactor some horrible code.

## Feature list

 * Support for OpenGL and Vulkan
 * Can draw 2D things on the screen in OpenGL-mode

## Design choices

Because "extensible", "fast" and "easy to use" don't go really well in the same phrase, I needed to do some considerations:

First of all, the API switch is compile-time with a simple template trick (dispatching via int and enums). While this actually works (and you can do startup runtime API switch, so you CAN select the API in runtime), you are forced to keep track of the API number.
This is not really a problem if you plan to use a single API (like only Vulkan or only OpenGL) because you can just store the integer in a `constexpr` variable and that's it; but if you want to switch API at startup, well, good luck. It shouldn't really be a PITA, but I might as well put this disclaimer.

"Why use templates? Just use an abstract class and `virtual` functions"

Well, there is the problem that `virtual` adds overhead and in an engine this is an issue. See, if it was only one or two classes, I can see the use of `virtual` (in that case, probably there wasn't much overhead), but here we're talking about the whole graphic system. This *can* kill performance. If you really want and easy one, [Sparky](https://github.com/TheCherno/Sparky/) did virtual-dispatch for API implementations.

The side-effect is that the engine is still extensible: You just need to use another number and you can introduce your own API in the engine (if you really want).

## TODO / Broken stuff

Strict engine stuff:

 * Finish the Vulkan port so I can fix bugs
   * Implement GLFW mouse support (again)
 * Implement basic 2D stuff (like rotations)
 * Basic event system
 * Basic sound system
 * GUI (probably a wrapper around [nuklear](https://github.com/vurtun/nuklear))
 * Particle system
 * VFS
 * 3D (?)
 * Optimizations (cache, algorithms, multi-threading, etc...)
 * Code cleanup
 
Addons:

 * Serialization module and custom binary reader
 * Network module (probably a wrapper around enet)
 * Mod loading? (LUA?)
