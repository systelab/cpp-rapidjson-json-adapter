from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, CMakeDeps
from conan.tools.files import copy, collect_libs
import os

class RapidJSONAdapterConan(ConanFile):
    name = "rapidjson-adapter"
    version = "1.2.0"
    description = "C++ JSON adapter based on rapidjson"
    url = "https://github.com/systelab/cpp-rapidjson-json-adapter"
    homepage = "https://github.com/systelab/cpp-rapidjson-json-adapter"
    author = "CSW <csw@werfen.com>"
    topics = ("conan", "rapidjson", "json", "wrapper")
    license = "MIT"
    settings = "os", "compiler", "build_type", "arch"
    exports_sources = "*", "!build/*", "!*.yml", "!*.md", "!*.in", "!ci", "!.gitattributes", "!.gitignore", "!LICENSE"

    def generate(self):
        tc = CMakeToolchain(self)
        tc.build_type = str(self.settings.build_type)
        tc.generate()
        CMakeDeps(self).generate()

    def requirements(self):
        self.requires("json-adapter-interface/1.2.0")
        self.requires("rapidjson/1.2.0")

    def build_requirements(self):
        self.tool_requires("gtest/1.14.0")
        self.tool_requires("rapidjson/1.2.0")
        self.tool_requires("json-adapter-test-utilities/1.2.0")
        self.test_requires("json-adapter-test-utilities/1.2.0")

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        include_src = os.path.join(self.source_folder, "src", "RapidJSONAdapter")
        include_dst = os.path.join(self.package_folder, "include", "RapidJSONAdapter")
        lib_dst = os.path.join(self.package_folder, "lib")
        lib_src = os.path.join(self.build_folder, "lib", str(self.settings.build_type))
        
        copy(self, "JSONAdapter.h", src=include_src, dst=include_dst)
        copy(self, "*.lib", src=lib_src, dst=lib_dst)
        copy(self, "*.pdb", src=lib_src, dst=lib_dst)
        copy(self, "*.a",   src=lib_src, dst=lib_dst)

    def package_info(self):
        self.cpp_info.libs = collect_libs(self)