cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

# set the project name
project(mpa LANGUAGES CXX)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# specify root dir, add cmake modules to path
set(MPA_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND CMAKE_MODULE_PATH ${MPA_ROOT_DIR}/cmake)

include(mpa_config)
include(mpa_compilers)
include(mpa_functions)
include(mpa_test)

add_subdirectory(mpabase)
add_subdirectory(mpalog)
add_subdirectory(mpaerror)

# Add examples
set(BUILD_EXAMPLES ON CACHE BOOL "Build project with examples" FORCE)
if(${BUILD_EXAMPLES})
    add_subdirectory(examples)
endif()



