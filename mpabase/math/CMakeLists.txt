cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

mpa_add_shared_library(
    NAME math
    TARGET_SOURCES src/mpamath.cpp
                   src/mpastandardalgorithms.cpp
                   src/mpastandardalgorithmsimpl.cpp
                   src/mpaintegeralgorithmsfactory.cpp
    PUBLIC_INCL include ../tools
    PRIVATE_INCL src/
    PUBLIC_LINK_LIB mpacore
    PRIVATE_LINK_LIB mpalog mpaerror
    )

if(${BUILD_TESTING})
    add_subdirectory(test)
endif()
