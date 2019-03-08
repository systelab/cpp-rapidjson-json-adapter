cmake_minimum_required(VERSION 2.8.12)
project(PackageTest CXX)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(RapidJSONAdapterExample RapidJSONAdapterExample.cpp)
target_link_libraries(RapidJSONAdapterExample ${CONAN_LIBS})

# enable_testing()
# add_test(NAME RapidJSONAdapterExample
         # WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin
         # COMMAND RapidJSONAdapterExample)
