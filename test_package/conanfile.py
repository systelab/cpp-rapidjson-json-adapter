from conan import ConanFile
from conan.tools.cmake import CMake
from conan.tools.files import copy
import os

class RapidJSONAdapterTestConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeToolchain", "CMakeDeps"

    def requirements(self):
        self.requires(self.tested_reference_str)
        self.requires("json-adapter-interface/1.2.0")
        self.requires("rapidjson/1.2.0")

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

        bin_dir = os.path.join(self.build_folder, "test_bin")
        os.makedirs(bin_dir, exist_ok=True)
        copy(self, "*.dll", src=os.path.join(self.build_folder, "bin"), dst=bin_dir)
        copy(self, "*.so*", src=os.path.join(self.build_folder, "lib"), dst=bin_dir)
        copy(self, "*.dylib*", src=os.path.join(self.build_folder, "lib"), dst=bin_dir)

    def test(self):
        cmake = CMake(self)
        cmake.test()