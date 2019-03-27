#pragma once

#include "imgui.h"
#include "imgui_stdlib.h"


namespace tewi
{
    template <typename APIType>
    class Window;

    template <typename APIType>
    void initImGui(APIType, tewi::Window<APIType>& win);

    template <typename APIType>
    void shutdownImGui(APIType);

    template <typename APIType>
    void newFrameImGui(APIType, tewi::Window<APIType>& win);

    template <typename APIType>
    void renderImGui(APIType, tewi::Window<APIType>& win, ImDrawData* data);
}
