# Configure preprocessor definitions
add_compile_options(-D RAPIDJSON_HAS_STDSTRING=1)

# Add project folder into includes
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Configure RapidJSONAdapter static library
set(RAPIDJSON_ADAPTER RapidJSONAdapter)
file(GLOB_RECURSE RAPIDJSON_ADAPTER_SRC "*.cpp")
file(GLOB_RECURSE RAPIDJSON_ADAPTER_HDR "*.h")
add_library(${RAPIDJSON_ADAPTER} STATIC ${RAPIDJSON_ADAPTER_SRC} ${RAPIDJSON_ADAPTER_HDR})
