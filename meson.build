project('tewi', 'cpp')


asl = dependency('asl')
glew = dependency('glew')
glfw = dependency('glfw')
glm = dependency('glm')
stb = dependency('stb')

subdir('external')

tewi_dirs = include_directories('include')
tewi_src = [
    'src/Input/InputBuffer.cpp',
    'src/Physics/Collidable2D.cpp',
    'src/Utils/Clock.cpp',
    'src/Utils/TickTimer.cpp',
    'src/Utils/stb.cpp',
    'src/Video/Camera2D.cpp',
    'src/Platform/OpenGL/BatchRenderer2D.cpp',
    'src/Platform/OpenGL/Context.cpp',
    'src/Platform/OpenGL/Device.cpp',
    'src/Platform/OpenGL/IndexBuffer.cpp',
    'src/Platform/OpenGL/Instance.cpp',
    'src/Platform/OpenGL/Shader.cpp',
    'src/Platform/OpenGL/Swapchain.cpp',
    'src/Platform/OpenGL/TextureCache.cpp',
    'src/Platform/OpenGL/ImGuiBindings.cpp',
    'src/Platform/OpenGL/imgui_impl_opengl3.cpp',
    'src/Platform/OpenGL/imgui_impl_glfw.cpp',
    'src/Platform/NullRenderer/Shader.cpp',
    'src/Platform/NullRenderer/BatchRenderer2D.cpp',
    'src/Platform/NullRenderer/Context.cpp',
    'src/Platform/NullRenderer/Swapchain.cpp',
    'src/Platform/NullRenderer/Window.cpp',
    'src/Platform/NullRenderer/Device.cpp',
]

tewi_deps = [
    asl,
    glfw,
    glew,
    stb,
    glm,
    imgui
]

tewi_opts = [
    'c_std=c11',
    'cpp_std=c++17'
]


if meson.get_compiler('cpp').get_id() == 'msvc'
    tewi_args = [
        '/W4', '/permissive-', '/GR-'
    ]
else
    tewi_args = [
        '-DGLEW_STATIC',
        '-DTEWI_STATIC_LIB=1',
        '-Wall', '-Wextra', '-pedantic', '-Wpedantic',
        '-Weffc++', '-Wno-unused-const-variable',
        '-fno-rtti', '-fno-exceptions',
    ]

    if meson.get_compiler('cpp').get_id() == 'clang'
        tewi_args += '-Weverything'
        tewi_args += '-Wno-missing-prototypes'
    endif
endif

static_library('tewi',
        sources : tewi_src,
        include_directories : tewi_dirs,
        dependencies : tewi_deps,
        override_options : tewi_opts,
        cpp_args : tewi_args)
