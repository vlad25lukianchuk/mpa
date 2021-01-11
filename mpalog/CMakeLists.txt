cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

add_library(mpalog_object OBJECT src/mpalogbase.cpp
                                 src/mpalogbase.h)
target_include_directories(mpalog_object PUBLIC src)

mpa_add_shared_library(
    NAME mpalog
    TARGET_SOURCES src/mpalog.cpp
    PRIVATE_LINK_LIB mpalog_object
    PUBLIC_INCL include
    )
