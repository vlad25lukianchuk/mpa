# Configure compilers and appropriate options
set(MIN_GNU_COMP_VER 9.3.0)
set(MIN_CLANG_COMP_VER 10.0.0)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Consider all warnings as errors
if(MSVC)
    set(MPA_WARNINGS "/WX /W4")
else()
    set(MPA_WARNINGS "-Werror -Wall -Wextra -Wconversion -Wsign-conversion")
endif()

# Build types compiler options
set(COVERAGE_COMPILER_FLAGS "--coverage")

if(MSVC)
    set(DEBUG_COMPILER_FLAGS "/Od")
    set(RELEASE_COMPILER_FLAGS "/O2")
else()
    set(DEBUG_COMPILER_FLAGS "-g3 -O0")
    set(RELEASE_COMPILER_FLAGS "-O3")
endif()

if(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    if(${CMAKE_CXX_COMPILER_VERSION} LESS ${MIN_GNU_COMP_VER})
        message(FATAL_ERROR "GNU CXX compiler version required 9.3.0
            or higher.")
    endif()
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    if(${CMAKE_CXX_COMPILER_VERSION} LESS ${MIN_CLANG_COMP_VER})
        message(FATAL_ERROR "Clang compiler version required 10.0.0 or higher.")
    endif()
endif()

if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${DEBUG_COMPILER_FLAGS} ${MPA_WARNINGS}")
elseif("${CMAKE_BUILD_TYPE}" STREQUAL "Coverage")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${DEBUG_COMPILER_FLAGS} ${COVERAGE_COMPILER_FLAGS} ${MPA_WARNINGS}")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${RELEASE_COMPILER_FLAGS} ${MPA_WARNINGS}")
endif()
