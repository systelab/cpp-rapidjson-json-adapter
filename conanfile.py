from conans import ConanFile, CMake, tools


class RapidJSONAdapterConan(ConanFile):
    name = "RapidJSONAdapter"
    description = "C++ JSON adapter based on rapidjson"
    url = "https://github.com/systelab/cpp-rapidjson-json-adapter"
    homepage = "https://github.com/systelab/cpp-rapidjson-json-adapter"
    author = "CSW <csw@werfen.com>"
    topics = ("conan", "rapidjson", "json", "wrapper")
    license = "MIT"
    generators = "cmake_find_package"
    settings = "os", "compiler", "build_type", "arch"
    options = {"gtest": ["1.7.0", "1.8.1", "1.10.0"]}
    default_options = "gtest=1.10.0"
    exports_sources = "*", "!build-*"

    def configure(self):
        self.options["JSONAdapterTestUtilities"].gtest = self.options.gtest

    def requirements(self):
        self.requires("JSONAdapterInterface/1.1.3@systelab/stable")
        self.requires("rapidjson/1.1.0.1@systelab/stable")

    def build_requirements(self):
        self.build_requires("JSONAdapterTestUtilities/1.1.3@systelab/stable")
        if self.options.gtest == "1.7.0":
            self.build_requires("gtest/1.7.0@systelab/stable")
        elif self.options.gtest == "1.8.1":
            self.build_requires("gtest/1.8.1")
        else:
            self.build_requires("gtest/1.10.0#0c895f60b461f8fee0da53a84d659131")

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def imports(self):
        self.copy("*.dll", dst="bin", src="bin")
        self.copy("*.dylib*", dst="bin", src="lib")
        self.copy("*.so*", dst="bin", src="lib")

    def package(self):
        self.copy("JSONAdapter.h", dst="include/RapidJSONAdapter", src="src/RapidJSONAdapter")
        self.copy("*RapidJSONAdapter.lib", dst="lib", keep_path=False)
        self.copy("*RapidJSONAdapter.pdb", dst="lib", keep_path=False)
        self.copy("*RapidJSONAdapter.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = tools.collect_libs(self)
