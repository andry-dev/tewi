imgui_src = [
    'imgui/imgui.cpp',
    'imgui/imgui_draw.cpp',
    'imgui/imgui_widgets.cpp',
    'imgui/misc/cpp/imgui_stdlib.cpp',
]

imgui_dirs = include_directories('imgui')

imgui_lib = static_library('ImGui-static', sources : imgui_src, include_directories : imgui_dirs)

imgui = declare_dependency(link_with : imgui_lib, include_directories: imgui_dirs)
