#pragma once

#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>

#include <tewi/Common.h>

namespace tewi
{
    template <typename APIType>
    struct Window;

    template <typename APIType>
    void TEWI_EXPORT initImGui(APIType, tewi::Window<APIType>& win);

    template <typename APIType>
    void TEWI_EXPORT shutdownImGui(APIType);

    template <typename APIType>
    void TEWI_EXPORT newFrameImGui(APIType, tewi::Window<APIType>& win);

    template <typename APIType>
    void TEWI_EXPORT renderImGui(APIType, tewi::Window<APIType>& win, ImDrawData* data);
} // namespace tewi
