cmake_minimum_required(VERSION 3.2)

macro(configure_google_test)
    # Download and unpack googletest at configure time
    configure_file(GoogleTest.in googletest-download/CMakeLists.txt)
    execute_process(COMMAND ${CMAKE_COMMAND} -G ${CMAKE_GENERATOR} .
                    RESULT_VARIABLE result
                    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download)
    if(result)
      message(FATAL_ERROR CMake step for googletest failed ${result})
    endif()

    execute_process(COMMAND ${CMAKE_COMMAND} --build .
                    RESULT_VARIABLE result
                    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download)
    if(result)
      message(FATAL_ERROR Build step for googletest failed ${result})
    endif()

	# Prevent overriding the parent project's compiler/linker settings on Windows
	set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    # Add googletest directly to our build. This defines
    # the gtest and gtest_main targets.
    add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
                     ${CMAKE_BINARY_DIR}/googletest-build
                     EXCLUDE_FROM_ALL)
					 
	# Add GoogleTest to includes
	include_directories("${gtest_SOURCE_DIR}/include")
	include_directories("${gmock_SOURCE_DIR}/include")
	
	# Include cmake module for GoogleTest
	include(GoogleTest)
endmacro()

# Configure project
project(RapidjsonJSONAdapter)

# Setup google_test (before set bin dir)
configure_google_test()

# Configure environment
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_PDB_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Configure include directories
include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/test)
include_directories(${CMAKE_SOURCE_DIR}/test/TestUtilities)
include_directories(${CMAKE_SOURCE_DIR}/interface)
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add subprojects
add_subdirectory(${CMAKE_SOURCE_DIR}/src/RapidJSONAdapter)
add_subdirectory(${CMAKE_SOURCE_DIR}/test/TestUtilities/JSONAdapterTestUtilities)
add_subdirectory(${CMAKE_SOURCE_DIR}/test/RapidJSONAdapterTest)
