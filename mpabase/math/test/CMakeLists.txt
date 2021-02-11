cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

mpa_add_unittest(
    NAME addition
    TARGET_SOURCES ut_addition.cpp
    LINK_LIBS mpamath gtest_main
    )
