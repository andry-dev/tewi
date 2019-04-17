#include <tewi/Video/BatchRenderer2D.hpp>
#include <tewi/Video/Window.hpp>
#include <tewi/Input/InputBuffer.hpp>
#include <tewi/Video/Sprite.h>

int main()
{
    using def_tag = tewi::API::OpenGLTag;
    using BatchRenderer2D = tewi::Renderer2D<def_tag, tewi::BatchRenderer2D>;

    tewi::Window<def_tag> win{"Test", tewi::Width{800}, tewi::Height{600}};
    BatchRenderer2D rend{};

    tewi::InputBuffer inputBuff;
    win.bindTo(inputBuff);

    tewi::Sprite<def_tag> spr(glm::vec2{0.0f, 0.0f}, "test.png");

    while (!win.isClosed())
    {
        win.pollEvents(inputBuff);

        rend.begin();
        rend.add(spr.getRenderable());
        rend.end();
        rend.draw();

        win.clear();
        win.swapBuffers();
    }
}
