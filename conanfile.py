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
        self.requires("rapidjson/1.1.0@bincrafters/stable")

    def package(self):
        self.copy("*.h", dst="include/JSONAdapterInterface", src="extern/JSONAdapter/JSONAdapterInterface")
        self.copy("*.h", dst="include/JSONAdapterTestUtilities", src="extern/JSONAdapter/JSONAdapterTestUtilities")
        self.copy("*.h", dst="include/RapidJSONAdapter", src="src/RapidJSONAdapter")
        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.dylib*", dst="lib", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = tools.collect_libs(self)
