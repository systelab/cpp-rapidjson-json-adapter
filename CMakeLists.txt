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

macro(configure_test_utilities_interface)
	# Check if git is available
	find_package(Git)
	if(NOT GIT_FOUND)
		message(FATAL_ERROR "git not found!")
	endif()

	# Clone the test utilities interface repository
	if(EXISTS ${CMAKE_SOURCE_DIR}/test/TestUtilities/TestUtilitiesInterface)
		message(STATUS "test/TestUtilities/TestUtilitiesInterface directory found, pulling...")
		execute_process(
                COMMAND             ${GIT_EXECUTABLE} pull origin master
                COMMAND             ${GIT_EXECUTABLE} submodule update --remote
                WORKING_DIRECTORY   ${CMAKE_SOURCE_DIR}
                OUTPUT_VARIABLE     git_output)
	else()
		message(STATUS "test/TestUtilities/TestUtilitiesInterface directory not found, cloning...")
		execute_process(
				COMMAND             ${GIT_EXECUTABLE} clone https://github.com/systelab/cpp-json-adapter-test-utilities.git test/TestUtilities/TestUtilitiesInterface
				WORKING_DIRECTORY   ${CMAKE_SOURCE_DIR}
				OUTPUT_VARIABLE     git_output)
	endif()
	
	# Checkout the right branch
	set(TEST_UTILITIES_INTERFACE_BRANCH master)
	message(STATUS "Checking out ${TEST_UTILITIES_INTERFACE_BRANCH} branch...")
	execute_process(
			COMMAND             ${GIT_EXECUTABLE} checkout ${TEST_UTILITIES_INTERFACE_BRANCH}
			WORKING_DIRECTORY   ${CMAKE_SOURCE_DIR}
			OUTPUT_VARIABLE     git_output)	
endmacro()

macro(configure_json_adapter_test_utilities)
	# Check if git is available
	find_package(Git)
	if(NOT GIT_FOUND)
		message(FATAL_ERROR "git not found!")
	endif()

	# Clone the JSON adapter test utilities repository
	if(EXISTS ${CMAKE_SOURCE_DIR}/test/TestUtilities/JSONAdapterTestUtilities)
		message(STATUS "test/TestUtilities/JSONAdapterTestUtilities directory found, pulling...")
		execute_process(
                COMMAND             ${GIT_EXECUTABLE} pull origin master
                COMMAND             ${GIT_EXECUTABLE} submodule update --remote
                WORKING_DIRECTORY   ${CMAKE_SOURCE_DIR}
                OUTPUT_VARIABLE     git_output)
	else()
		message(STATUS "test/TestUtilities/JSONAdapterTestUtilities directory not found, cloning...")
		execute_process(
				COMMAND             ${GIT_EXECUTABLE} clone https://github.com/systelab/cpp-json-adapter-test-utilities.git test/TestUtilities/JSONAdapterTestUtilities
				WORKING_DIRECTORY   ${CMAKE_SOURCE_DIR}
				OUTPUT_VARIABLE     git_output)
	endif()
	
	# Checkout the right branch
	set(TEST_UTILITIES_INTERFACE_BRANCH master)
	message(STATUS "Checking out ${TEST_UTILITIES_INTERFACE_BRANCH} branch...")
	execute_process(
			COMMAND             ${GIT_EXECUTABLE} checkout ${TEST_UTILITIES_INTERFACE_BRANCH}
			WORKING_DIRECTORY   ${CMAKE_SOURCE_DIR}
			OUTPUT_VARIABLE     git_output)	
endmacro()

macro(update_submodules)
	message(STATUS "Updating submodules...")
	execute_process(
			COMMAND             ${GIT_EXECUTABLE} submodule update --init --recursive
			WORKING_DIRECTORY   ${CMAKE_SOURCE_DIR}
			OUTPUT_VARIABLE     git_output)	
endmacro()

macro(configure_standalone)
	# Configure project
	project(RapidJSONAdapter)

	# Setup google_test (before set bin dir)
	configure_google_test()
	
	# Setup external test utilities repositories
	configure_test_utilities_interface()
	configure_json_adapter_test_utilities()
	update_submodules();

	# Configure environment
	set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
	set(CMAKE_CXX_STANDARD 14)
	set(CMAKE_CXX_STANDARD_REQUIRED ON)
	
	# Configure include directories
	include_directories(${CMAKE_SOURCE_DIR}/include)
	include_directories(${CMAKE_SOURCE_DIR}/interface)
	include_directories(${CMAKE_SOURCE_DIR}/src)
	include_directories(${CMAKE_SOURCE_DIR}/test)
	include_directories(${CMAKE_SOURCE_DIR}/test/TestUtilities)
	
	# Add test subprojects
	add_subdirectory(${CMAKE_SOURCE_DIR}/test/TestUtilities/JSONAdapterTestUtilities)
	add_subdirectory(${CMAKE_SOURCE_DIR}/test/RapidJSONAdapterTest)	
endmacro()


# Configure project to be standalone
if (CMAKE_BUILD_TYPE STREQUAL "RapidjsonJSONAdapterStandalone")
	configure_standalone()
endif()

# Add library subproject
add_subdirectory(${CMAKE_SOURCE_DIR}/src/RapidJSONAdapter)
