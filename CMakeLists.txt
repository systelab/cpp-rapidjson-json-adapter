cmake_minimum_required(VERSION 3.2)

project(RapidJSONAdapter)

# Configure environment
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Adjust compilation flags
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error=implicit-fallthrough")
endif()

# Setup up Google test
include(ConfigureGoogleTest)
configure_google_test()

# Setup extern repositories
include(GitCloneRepository)
git_clone_repository(URL https://github.com/systelab/cpp-test-utilities.git DIR extern/TestUtilities BRANCH v1.0.1)
git_clone_repository(URL https://github.com/systelab/cpp-json-adapter.git   DIR extern/JSONAdapter   BRANCH v1.0.2)

# Configure include directories
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/test)
include_directories(${CMAKE_SOURCE_DIR}/extern/JSONAdapter)

# Add subprojects
add_subdirectory(${CMAKE_SOURCE_DIR}/src/RapidJSONAdapter)
add_subdirectory(${CMAKE_SOURCE_DIR}/extern/JSONAdapter/JSONAdapterTestUtilities)
add_subdirectory(${CMAKE_SOURCE_DIR}/test/RapidJSONAdapterTest)
