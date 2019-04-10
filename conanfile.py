from conans import ConanFile, tools

class RapidJSONAdapterConan(ConanFile):
    name = "RapidJSONAdapter"
    description = "C++ JSON adapter based on rapidjson"
    url = "https://github.com/systelab/cpp-rapidjson-json-adapter"
    homepage = "https://github.com/systelab/cpp-rapidjson-json-adapter"
    author = "CSW <csw@werfen.com>"
    topics = ("conan", "rapidjson", "json", "wrapper")
    license = "MIT"
    generators = "cmake"
    settings = "os", "compiler", "build_type", "arch"

    def requirements(self):
        self.requires("JSONAdapter/1.0.0@systelab/stable")
        self.requires("rapidjson/1.1.0@bincrafters/stable")

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
