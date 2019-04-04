cmake_minimum_required(VERSION 3.2)

project(RapidJSONAdapterPackageTestProject)

# Configure environment
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-DRAPIDJSON_HAS_STDSTRING=1)

# Setup 3rd party libraries through conan
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# Configure test package project
set(RAPIDJSON_ADAPTER_PACKAGE_TEST_PROJECT RapidJSONAdapterPackageTest)
add_executable(${RAPIDJSON_ADAPTER_PACKAGE_TEST_PROJECT} RapidJSONAdapterExample.cpp)
target_link_libraries(${RAPIDJSON_ADAPTER_PACKAGE_TEST_PROJECT} ${CONAN_LIBS})
