cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

mpa_add_shared_library(
    NAME error
    TARGET_SOURCES src/mpaexcept.cpp
    PUBLIC_INCL include
    PRIVATE_INCL src
    )
