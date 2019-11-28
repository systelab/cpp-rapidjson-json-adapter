enable_testing()

# Add project folder into includes
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Find external dependencides
find_package(JSONAdapterTestUtilities)
find_package(gtest)

# Configure test project
set(RAPIDJSON_ADAPTER_TEST_PROJECT RapidJSONAdapterTest)
file(GLOB_RECURSE RAPIDJSON_ADAPTER_TEST_PROJECT_SRC "*.cpp")
file(GLOB_RECURSE RAPIDJSON_ADAPTER_TEST_PROJECT_HDR "*.h")
add_executable(${RAPIDJSON_ADAPTER_TEST_PROJECT} ${RAPIDJSON_ADAPTER_TEST_PROJECT_SRC} ${RAPIDJSON_ADAPTER_TEST_PROJECT_HDR})
target_link_libraries(${RAPIDJSON_ADAPTER_TEST_PROJECT} RapidJSONAdapter JSONAdapterTestUtilities::JSONAdapterTestUtilities gtest::gtest)

# Ignored missing PDBs link warning on Visual Studio
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set_target_properties(${RAPIDJSON_ADAPTER_TEST_PROJECT} PROPERTIES LINK_FLAGS "/ignore:4099")
endif()

#Configure source groups
foreach(FILE ${RAPIDJSON_ADAPTER_TEST_PROJECT_SRC} ${RAPIDJSON_ADAPTER_TEST_PROJECT_HDR}) 
    get_filename_component(PARENT_DIR "${FILE}" DIRECTORY)
    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" GROUP "${PARENT_DIR}")
    string(REPLACE "/" "\\" GROUP "${GROUP}")

    if ("${FILE}" MATCHES ".*\\.cpp")
       set(GROUP "Source Files${GROUP}")
    elseif("${FILE}" MATCHES ".*\\.h")
       set(GROUP "Header Files${GROUP}")
    endif()

    source_group("${GROUP}" FILES "${FILE}")
endforeach()

# Register tests
add_test(NAME RapidJSONAdapterTest COMMAND ${RAPIDJSON_ADAPTER_TEST_PROJECT})

# Additional target for code coverage analysis
if (CMAKE_BUILD_TYPE STREQUAL "Coverage")
	include(CodeCoverage)
	setup_target_for_coverage(RapidJSONAdapterTestCoverage RapidJSONAdapterTest coverage)
endif()
