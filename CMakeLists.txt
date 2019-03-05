cmake_minimum_required(VERSION 3.2)

project(RapidJSONAdapter)

# Configure environment
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Setup 3rd party libraries through conan
include(Conan)
conan_cmake_run(REQUIRES gtest/1.8.1@bincrafters/stable
                         rapidjson/1.1.0@bincrafters/stable
                BASIC_SETUP
                BUILD missing)

# Setup extern repositories
include(GitCloneRepository)
git_clone_repository(URL https://github.com/systelab/cpp-test-utilities.git DIR extern/TestUtilities BRANCH master)
git_clone_repository(URL https://github.com/systelab/cpp-json-adapter.git   DIR extern/JSONAdapter   BRANCH master)

# Configure include directories
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/test)

# Add subprojects
add_subdirectory(${CMAKE_SOURCE_DIR}/src/RapidJSONAdapter)
add_subdirectory(${CMAKE_SOURCE_DIR}/test/RapidJSONAdapterTest)
add_subdirectory(${CMAKE_SOURCE_DIR}/extern/JSONAdapter/JSONAdapterTestUtilities)
