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
    options = {"gtest": ["1.7.0", "1.8.1"]}
    default_options = "gtest=1.8.1"

    def configure(self):
        self.options["JSONAdapterTestUtilities"].gtest = self.options.gtest

    def build_requirements(self):
        self.build_requires("JSONAdapterTestUtilities/1.0.4@systelab/stable")
        if self.options.gtest == "1.7.0":
            self.build_requires("gtest/1.7.0@systelab/stable")
        else:
            self.build_requires("gtest/1.8.1@bincrafters/stable")

    def requirements(self):
        self.requires("JSONAdapterInterface/1.0.4@systelab/stable")
        self.requires("rapidjson/1.1.0@bincrafters/stable")

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
