#include "tewi/Video/Window.hpp"
#include "tewi/Video/API/API.h"
#include "tewi/Input/InputBuffer.hpp"
#include "tewi/Utils/Log.h"

#include <string>

using def_api = tewi::API::OpenGLTag;

int main()
{
    tewi::Window<def_api> win("Test", tewi::Width{800}, tewi::Height{600});

    tewi::InputBuffer buff;
    win.bindTo(buff);

    while (!win.isClosed())
    {
        win.pollEvents(buff);

        auto events = buff.queryEvents();

        for (const auto& x : events)
        {
            tewi::Log::info(std::to_string(static_cast<asl::i16>(x.type)));
        }

        win.clear();
        win.swapBuffers();
    }
}
