include(FetchContent)

FetchContent_Declare(
  asl
  GIT_REPOSITORY https://github.com/andry-dev/asl.git
)

FetchContent_MakeAvailable(asl)
#add_subdirectory(asl)

if (TEWI_INTEGRATE_IMGUI)

    FetchContent_Declare(
      imgui
      GIT_REPOSITORY https://github.com/ocornut/imgui.git
    )

    FetchContent_MakeAvailable(imgui)

    add_library(ImGui
                ${imgui_SOURCE_DIR}/imgui.cpp
                ${imgui_SOURCE_DIR}/imgui_draw.cpp
                ${imgui_SOURCE_DIR}/imgui_widgets.cpp
                ${imgui_SOURCE_DIR}/misc/cpp/imgui_stdlib.cpp)
            target_include_directories(ImGui SYSTEM PUBLIC ${imgui_SOURCE_DIR} ${imgui_SOURCE_DIR}/misc/cpp/)

endif()

