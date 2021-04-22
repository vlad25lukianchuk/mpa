cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

mpa_add_executable(
    NAME simple_add
    TARGET_SOURCES simple_add.cpp
    LINK_LIBS mpainterface
    )
