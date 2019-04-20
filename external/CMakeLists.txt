if (TEWI_INTEGRATE_IMGUI)
    add_library(ImGui STATIC
                imgui/imgui.cpp
                imgui/imgui_draw.cpp
                imgui/imgui_widgets.cpp
                imgui/misc/cpp/imgui_stdlib.cpp)
    target_include_directories(ImGui SYSTEM PUBLIC imgui/ imgui/misc/cpp/)
endif()

