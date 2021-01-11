# configure compilers and appropriate options
set(MIN_GNU_COMP_VER 9.3.0)
set(MIN_CLANG_COMP_VER 10.0.0)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# consider all warnings
set(MPA_WARNINGS "-Wall -Wextra")

# build types compiler options
set(COVERAGE_COMPILER_FLAGS "--coverage")
set(DEBUG_COMPILER_FLAGS "-g3 -O0")
set(RELEASE_COMPILER_FLAGS "-O3")

if(NOT ${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU"
        AND NOT ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    message(FATAL_ERROR "Unsupported compiler. Must be GNU CXX or Clang.")
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
