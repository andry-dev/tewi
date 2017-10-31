#include "../../include/Video/BatchRenderer2D.hpp"

using namespace tewi;
using namespace tewi::API;

void simple_usage()
{
    /* First of all we specify the API and then what type of renderer we want.
     * At the moment I have implemented only a batch renderer, but in the future
     * I'll implement deferred rendering, checkboard rendering, etc...
     *
     * You can even create your own, but that's for later
     */

    Renderer2D<OpenGLTag, BatchRenderer2D> batch;

    // Then we can create our sprite class. I'll do it inline because this is an
    // example, you should create a class in another file.

    class Character
    {
    public:
        Character()
            : m_renderable(
                    {1.0, 2.0}, // Position
                    {1.0, 1.0}, // Size
                    { 255, 255, 255, 255 }) // Color
        {  }

        // ...

        auto getRenderable() const { return m_renderable; }

        // Heck, you can even use operator overloading if you want to:
        // operator const Renderable2D() { return m_renderable; }
    private:
        Renderable2D m_renderable;
    };

    Character hero;

    /* You really want to make Renderable2D part of your class, don't inherit
     * from it.
     *
     * Alternatively, you can do it in a DOD-way and create a structure of
     * arrays containing Renderable2D; the canvas is yours.
     *
     *
     * It doesn't have a default constructor, you need to initialize it.
     */

    // And now we can start rendering to the screen:

    // Begin the rendering.
    // PS: I hate this but for performance reasons it's necessary.
    batch.begin();

    // Add your Renderable2Ds, it can also accept a std::vector of renderables.
    batch.add(hero.getRenderable());
    // Or with operator overloading:
    // batch.add(hero);
    
    // End the rendering.
    batch.end();

    // Finally draw.
    batch.draw();
    
    // NOTE: The API for the constructor or the draw() function may change to
    // accomodate a Vulkan Swapchain
}

// "You're slow, I want my own rendering class"
// Sure bud:


// Create your own policy
template <typename APIType>
struct DeferredRenderer2D
{
protected:

    void begin()
    {
    }

    void add(const Renderable2D& renderable)
    {
    }

    void add(const std::vector<Renderable2D>& renderableList)
    {
    }

    void end()
    {
    }

    void draw()
    {
    }

public:

    // You can even expose your functions and the client-code will be able to
    // call them.
    void my_func()
    {

    }
};

// Specialize it for the various APIs

template <>
struct DeferredRenderer2D<OpenGLTag>
{
protected:

    void begin()
    {
    }

    void add(const Renderable2D& renderable)
    {
    }

    void add(const std::vector<Renderable2D>& renderableList)
    {
    }

    void end()
    {
    }

    void draw()
    {
    }

public:

    void my_func()
    {

    }

private:
    // You can also create members, there's no limitation.
    // Do literally whatever you want.
    int m_num = 0;
};

template <>
struct DeferredRenderer2D<VulkanTag>
{
protected:

    void begin()
    {
    }

    void add(const Renderable2D& renderable)
    {
    }

    void add(const std::vector<Renderable2D>& renderableList)
    {
    }

    void end()
    {
    }

    void draw()
    {
    }

public:

    void my_func()
    {

    }
};

// You can use your own API tag if you want to extend this engine and support
// APIs like Metal or Direct3D.

void custom_renderer()
{
    // Create your new renderer.
    Renderer2D<OpenGLTag, DeferredRenderer2D> deferred;

    // And use it as you did before

    deferred.begin();

    // ...
}
