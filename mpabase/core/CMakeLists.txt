cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

mpa_add_shared_library(
    NAME mpacore
    TARGET_SOURCES src/mpanumber.cpp
                   src/coreutils.cpp
    PUBLIC_INCL include
    PRIVATE_INCL src/
    PRIVATE_LINK_LIB mpalog
    )
