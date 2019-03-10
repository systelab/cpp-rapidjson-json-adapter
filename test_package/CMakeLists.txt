cmake_minimum_required(VERSION 2.8.12)
project(RapidJSONAdapterPackageTestProject CXX)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(RAPIDJSON_ADAPTER_PACKAGE_TEST_PROJECT RapidJSONAdapterPackageTest)
add_executable(${RAPIDJSON_ADAPTER_PACKAGE_TEST_PROJECT} RapidJSONAdapterExample.cpp)
target_link_libraries(${RAPIDJSON_ADAPTER_PACKAGE_TEST_PROJECT} ${CONAN_LIBS})
