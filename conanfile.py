from conans import ConanFile, CMake, tools

class TewiConan(ConanFile):
    name = "tewi"
    version = "0.1"
    license = "MIT"
    url = "https://github.com/andry-dev/tewi.git"
    description = "An easy to use, extendable, game engine"
    settings = "os", "compiler", "build_type", "arch"

    options = {
        "shared": [True, False],
        "integrate_imgui": [True, False],
        "enable_vulkan": [True, False]
    }

    default_options = {
        "shared": False,
        "integrate_imgui": True,
        "enable_vulkan": False
    }

    requires = (
        ("glfw/3.2.1@bincrafters/stable"),
        ("glew/2.1.0@bincrafters/stable"),
        ("glm/0.9.9.4@g-truc/stable"),
        ("stb/20180214@conan/stable"),
        ("asl/0.1@andry/dev")
    )


    generators = "cmake", "pkg_config"
    exports_sources = "*",

    def configure(self):
        if self.options.integrate_imgui:
            self.exports_sources += "external/imgui/*",

    def build(self):
        cmake = CMake(self)
        imgui = "-DTEWI_INTEGRATE_IMGUI=1" if self.options.integrate_imgui else "-DTEWI_INTEGRATE_IMGUI=0"
        vulkan = "-DTEWI_ENABLE_VULKAN=1" if self.options.enable_vulkan else "-DTEWI_ENABLE_VULKAN=0"
        self.run("cmake . %s %s %s" % (cmake.command_line, imgui, vulkan))
        self.run("cmake --build . %s" % cmake.build_config)
        #cmake.configure(source_folder=".")
        #self.run("cmake --build .")


    def package(self):
        self.copy("*.h", dst="include", src="include")
        self.copy("*.hpp", dst="include", src="include")
        self.copy("*.hxx", dst="include", src="include")

        if self.options.integrate_imgui:
            self.copy("*.h", dst="include", src="external/imgui")

        self.copy("*libtewi.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.dylib", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["tewi", "ImGui"]
