#include <tewi/Video/Window.hpp>
#include <tewi/Input/InputBuffer.hpp>

#include <tewi/Utils/ImGuiBindings.h>

using def_api = tewi::API::OpenGLTag;

int main()
{
    tewi::Window<def_api> win("Imgui", tewi::Width{800}, tewi::Height{600});

    tewi::InputBuffer inputBuffer;
    win.bindTo(inputBuffer);

    ImGui::CreateContext();
    ImGui::StyleColorsLight();
    tewi::initImGui(def_api{}, win);

    while (!win.isClosed())
    {
        win.pollEvents(inputBuffer);

        tewi::newFrameImGui(def_api{}, win);
        ImGui::NewFrame();

        {
            ImGui::Begin("Hello");

            if (ImGui::Button("Test button"))
            {
                tewi::Log::info(":)");
            }

            ImGui::End();
        }


        ImGui::Render();

        win.clear();

        tewi::renderImGui(def_api{}, win, ImGui::GetDrawData());

        win.swapBuffers();
    }

    tewi::shutdownImGui(def_api{});
    ImGui::DestroyContext();
}
