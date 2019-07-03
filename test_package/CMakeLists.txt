cmake_minimum_required(VERSION 3.2)

project(RapidJSONAdapterPackageTestProject)

# Configure environment
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../cmake ${CMAKE_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Find external dependencies
find_package(RapidJSONAdapter)

# Configure compilation options
add_compile_options(-DRAPIDJSON_HAS_STDSTRING=1)

# Configure test package project
set(RAPIDJSON_ADAPTER_PACKAGE_TEST_PROJECT RapidJSONAdapterPackageTest)
add_executable(${RAPIDJSON_ADAPTER_PACKAGE_TEST_PROJECT} RapidJSONAdapterExample.cpp)
target_link_libraries(${RAPIDJSON_ADAPTER_PACKAGE_TEST_PROJECT} RapidJSONAdapter::RapidJSONAdapter)

# Register tests
enable_testing()
add_test(NAME RapidJSONAdapterPackageTest COMMAND ${RAPIDJSON_ADAPTER_PACKAGE_TEST_PROJECT})
