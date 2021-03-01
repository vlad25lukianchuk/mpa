cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

mpa_add_shared_library(
    NAME mpacore
    TARGET_SOURCES src/mpanumber.cpp
                   src/mpacoreutils.cpp
    PUBLIC_INCL include
    PRIVATE_INCL src/
    PRIVATE_LINK_LIB mpalog mpaerror
    )

if(${BUILD_TESTING})
    add_subdirectory(test)
endif()
