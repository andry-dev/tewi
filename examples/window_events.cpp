#include "tewi/Video/Window.hpp"
#include "tewi/Video/API/API.h"

#include <string>

using def_api = tewi::API::OpenGLTag;

int main()
{
    tewi::Window<def_api> win("Test", tewi::Width{800}, tewi::Height{600});

    while (!win.isClosed())
    {
        win.pollEvents();

        auto event = win.lastEvent();
        if ((event).type == tewi::WindowEvent::Type::KeyEscape)
        {
            win.forceClose();
        }
        tewi::Log::info(std::to_string(static_cast<asl::i16>(event.type)));


        win.clear();
        win.swapBuffers();
    }
}
