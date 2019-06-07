#include <tewi/Utils/ImGuiBindings.h>
#include <tewi/Video/API/API.h>

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <tewi/Video/Window.hpp>

namespace tewi
{
    template <>
    void initImGui(tewi::API::OpenGLTag,
                   tewi::Window<tewi::API::OpenGLTag>& win)
    {
        ImGui_ImplGlfw_InitForOpenGL(win.ptr(), true);
        ImGui_ImplOpenGL3_Init("#version 330 core");
    }

    template <>
    void shutdownImGui(tewi::API::OpenGLTag)
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
    }

    template <>
    void newFrameImGui(tewi::API::OpenGLTag,
                       tewi::Window<tewi::API::OpenGLTag>& win)
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
    }

    template <>
    void renderImGui(tewi::API::OpenGLTag, tewi::Window<tewi::API::OpenGLTag>&,
                     ImDrawData* data)
    {
        ImGui_ImplOpenGL3_RenderDrawData(data);
    }
} // namespace tewi
