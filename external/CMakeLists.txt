if (TEWI_INTEGRATE_IMGUI)
    file(GLOB test-imguidir imgui/imgui*)
    if (test-imguidir)
        set(FOUND_LOCAL_IMGUI 1 PARENT_SCOPE)
        add_library(ImGui STATIC
                    imgui/imgui.cpp
                    imgui/imgui_draw.cpp
                    imgui/imgui_widgets.cpp
                    imgui/misc/cpp/imgui_stdlib.cpp)

        target_include_directories(ImGui
            SYSTEM
            PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/imgui/>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/imgui/misc/cpp/>
            $<INSTALL_INTERFACE:imgui/>
            $<INSTALL_INTERFACE:imgui/misc/cpp/>)

        message(STATUS "[tewi] Found local imgui in external/imgui")
    else()
        set(FOUND_LOCAL_IMGUI 0 PARENT_SCOPE)
    endif()
endif()

add_subdirectory(tewi_loader)
