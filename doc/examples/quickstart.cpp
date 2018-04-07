#include "Common.h"
#include "Video/Window.hpp"
#include "Video/Shader.hpp"
#include "Video/Renderer2D.hpp"
#include "Video/BatchRenderer2D.hpp"

#include <array>

// The following example doesn't use GameCommon, it's completely self-contained
// No inheritance is used but it assumes a custom shader layout from the user
// Instead I do most stuff manually (well, there's no need to anyway)

using def_tag = tewi::API::OpenGLTag;

constexpr std::array<int, 22> g_shaderTexIDs =
{
    0,  1,  2,  3,  4,  5,  6, 7,
    8,  9,  10, 11, 12, 13, 14,
    15, 16, 17, 18, 19, 20, 21
};

int main()
{
    // Create the window
    tewi::Window<def_tag> win("Test app", 800, 600);

    // Doing raw GLFW calls
    // TODO: Wrap this uglyness in a struct
    auto keycallback = [](GLFWwindow* win, int key, int scancode,
                          int action, int mods)
    {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        {
            glfwWindowShouldClose(window);
        }
    };

    win.setKeyboardCallback(keycallback);


    // Create the renderer
    tewi::Renderer2D<def_tag, tewi::BatchRenderer2D> renderer;

    auto shader = renderer.createShaderProgram();

    // Create the damned sprite
    tewi::Sprite<def_tag> spr(glm::vec2(0.0f, 0.0f), "textures/sample.png");

    // Main loop
    while (!win.isWindowClosed())
    {
        // Update
        win.pollEvents();

        ///////////////////////////
        // DRAWING STARTS HERE
        ///////////////////////////

        // API-specific pre-drawing stuff
        win.getContext().preDraw();

        shader.enable();

        // TODO: The user should not manually do all of this
        tewi::setUniform(shader.getUniformLocation("textures"),
                         g_shaderTexIDs);

        renderer.begin();

        renderer.add(spr.getRenderable());

        renderer.end();

        renderer.draw();

        shader.disable();

        // API-specific post-drawing stuff
        win.getContext().postDraw();

        // Swap the window buffers
        win.swap();
    }
}
