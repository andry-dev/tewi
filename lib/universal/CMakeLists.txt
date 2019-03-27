add_library(ImGui
            imgui/imgui.cpp
            imgui/imgui_draw.cpp
            imgui/imgui_widgets.cpp
            imgui/misc/cpp/imgui_stdlib.cpp)
target_include_directories(ImGui SYSTEM PUBLIC imgui/ imgui/misc/cpp/)


# LICENSE.txt
# docs
# examples
# imconfig.h
# imgui.cpp
# imgui.h
# imgui_demo.cpp
# imgui_draw.cpp
# imgui_internal.h
# imgui_widgets.cpp
# imstb_rectpack.h
# imstb_textedit.h
# imstb_truetype.h
# misc
