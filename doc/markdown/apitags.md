Intro to API tags  {#apitags}
===

## So, what's the deal with API tags? Why are you creating a special page just for them?

First of all, let me make this clear: tewi is an _experimental_ engine, you
can think of it like a toy project. What I'm trying to do is avoiding `virtual`
(and strict OOP hierarchies) for most of the "core modules" in the engine; that
means most of the rendering classes (renderers, textures, shaders, ecc...).

This may work fine if you want to support only one graphics API, but with this
engine I want to support more graphics APIs (other than OpenGL), so I had to
come up with a solution: static polymorphism.

Through CRTP and policy-based design I would be able to support more than one 
graphic API via the use of tag types, and so I started experimenting with it.

## Graphics-related classes should auto-wire

The idea was to pass to every graphics-related class a template parameters that
tells what API it's currently using.

```cpp
// Test.h

template <typename APINum>
struct Test
{
    // Blank just as a "safe-default"
    // You can also use "= delete" to trigger a compiler-error
    void doSomething() { }
    int anotherThing() { }
};
```

then specialize the class for the relevant tag, changing **the entire
structure of it**:

```cpp
// Somewhere/Else/Test.h

template<>
struct Test<OpenGLTag>
{
    void doSomething()
    {
        std::cout << "Hi\n";
    }

    int anotherThing()
    {
        return 5;
    }
};
```

And then the user can just do this:

```cpp
Test<OpenGLTag> t;
t.doSomething();
```

If we are talking about pure API-dependent code (like a Shader) then it's
possible to agree to a common interface but change the inner-workings easily:

```cpp
// Shader.h
// General implementation / Common interface

template <typename Tag>
class Shader
{
public:
    void enable() { }
    void disable() { }
    // [...]
};


// OpenGL/Shader.h
// OpenGL-specific code goes here

template <>
class Shader<OpenGLTag>
{
public:
    void enable()
    {
         // [...]
    }

    void disable()
    {
         // [...]
    }

private:

    int m_id;
};
```

Or even with pure data like a platform-specifc texture:

```cpp
// Texture.h

// Intentionally empty
template <typename Tag>
struct Texture
{ };


// OpenGL/Texture.h

template <>
struct Texture<OpenGLTag>
{
    int id;
    float size[2];
};
```

This last example is kinda controversial though: I'm basically changing the
whole API of the Texture for a specific tag, how can this do any good?


## API-independent and API-dependent code

We're missing something big here: there are actually two users of this library:

* The ones that just don't care about implementing their own API so they will
    never mess around with tags.

* The ones that for some reason need to customize some parts of the library, so
    they are going to mess around with tags.

There are parts of tewi intended **only for the second group** (and the actual
developers, of course): there are classes that are API-specific and they can
work only with other API-specific code; in the case of Texture, the texture
loader and the renderers interacts with it. Note this: while the texture loader
and the renderers are used by the "normal" users of the library, the things that
they do and use are relevant only to developers and people who want to create
their own tag, so **only for those parts of the library, it's possible to
change the entire API of them**.

If you still don't understand what I'm saying, consider things this way:

Let it be user John. John wants to render a sprite with OpenGL:

```cpp
{
    Renderable2D<OpenGLTag> mysprite(
                            glm::vec2{0.0f, 0.0f},
                            ResourceManager<OpenGLTag, TextureCache>::getResource("textures/a.png"),
                            Color{255, 255, 255, 255});

    Renderer2D<OpenGLTag, BatchRenderer2D> renderer;
    renderer.add(mysprite);

    // [...]
}
```

The explicit (and long) call to the ResourceManager can be extracted to a
function but that's out of the scope of this example.

Now, John doesn't know what the hell is a `Texture<>`, he doesn't (and shouldn't)
create it explicitly, it was supplied by the `ResourceManager` and used in the
`BatchRenderer2D`. Now, the `ResourceManager<>` and the `BatchRenderer2D<>`
do not actually know _what_ a `Texture<>` is, not even _how_ it works, they
just know it exists. On the contrary, `ResourceManager<OpenGLTag>` and
`BatchRenderer2D<OpenGLTag>` know very well _what_ a `Texture<OpenGLTag>` is
_how_ it works.

Meet Markus. Markus is a special kind of person: for some reasons he wants to
mess with the mipmap levels of the generated texture, so he starts reading
about `TextureCache<>` and how it calls a function from API-independent code to
the relevant API-dependent piece:

```cpp
void genAPITexture(Texture<API::OpenGLTag>& tex, asl::mut_u8* imagePtr, asl::num width, asl::num height)
{
    glGenTextures(1, &tex.id);

    glBindTexture(GL_TEXTURE_2D, tex.id);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imagePtr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
}
```

Now, to John this is gibberish but to Markus this is _extremely important_: he
can implement his own tag that just overrides these defaults and he's set.
Well, it's also the creator's fault for not providing a saner level of
customization [yeah I'm working on it], but this should demonstrate the idea.

tl;dr: Various parts of the engine are made to be overridden with custom
configuration based on the graphics API but the rest should agree to a common
interface.


## On the topic of auto-wiring

There are changes that should not break the base API of the various classes,
allowing the "auto-wire" thingy that I was talking about:

```cpp
// Client-code

template <typename Tag>
class Foo
{
public:

    // [...]

private:

    Renderable2D<Tag> m_renderable;
    Renderer2D<Tag, BatchRenderer2D> m_renderer;
};

// On call site

// Let's pretend that there is a template parameter outside of this block named
// "Tag"
{
    Foo<Tag> f;
    // And so everything inside Foo is "automatically" deduced and the correct
    // API is used
}
```

## Adding tags

Since tags are basically empty `struct`s, if you want to introduce a completely
new graphics API, you can just create a new tag:

```cpp
struct MetalTag { };
```

And then have fun partially specializing most of the classes inside the Video/
directory. In particular, the most important stuff is in the Video/API/
directory: it mostly contains basic definitions for the initial initialization
of the API. Anyway the exact procedure will be documented in another page.

## Modifing existing tags

Maybe you don't want to implement a whole new API, maybe you just want to modify
existing code without touching this library, well there's a way even here:

You see, there's a "function" in the `Common.h` file called
`is_api_compatible_v`. It's not really a function per-se, it's actually a
variable template, but it's used in the library to check if two or more tags are
compatible. By "compatible" it means that they are:

* The same.
* One inherits from another.

So if you want to override something used with the OpenGL tag, you do this:

```cpp
struct MyCustomTag : public OpenGLTag { };
```

And then partially specialize the specific portion of code that you want to
change (it's recommended that you take a look at the implementation that you
want to override first):

```cpp
// Somewhere

template <>
class BatchRenderer2D<MyCustomTag>
{
public:
    // [...]

    template <typename T>
    void add(const Renderable2D<T>& r)
    {
        // [...]
    }
};
```

And then it should just work (if you didn't mess things up, obviously):

```cpp
Renderable2D<OpenGLTag> a{ /* ... */ };

Renderer2D<MyCustomTag, BatchRenderer2D> renderer;

renderere.add(a);
```

If you want to statically switch the tags used for a class, then you can use
`switch_api` (included in Common.h aswell):

```cpp
template <typename Tag>
void foo()
{
    Renderable2D<switch_api<Tag, OpenGLTag, MyCustomTag>> a{ /* ... */ };

    // [...]
}
```

This can be read as "if the current tag is `OpenGLTag` then change it to
`MyCustomTag`, else just use the tag normally", so if I were to call this
function with `OpenGLTag` then the tag of 'a' would be `MyCustomTag`, otherwise
if I call this function with `VulkanTag` the tag of 'a' would remain
`VulkanTag`.
