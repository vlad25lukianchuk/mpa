cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

mpa_add_shared_library(
    NAME interface
    TARGET_SOURCES src/mpainteger.cpp
    PUBLIC_INCL include
    PRIVATE_INCL src/
    PUBLIC_LINK_LIB mpacore
    PRIVATE_LINK_LIB mpalog mpamath
    )

if(${BUILD_TESTING})
    add_subdirectory(test)
endif()
