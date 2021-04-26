cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

mpa_add_unittest(
    NAME basic_errors
    TARGET_SOURCES ut_basic_errors.cpp
    LINK_LIBS mpaerror gtest_main
    )
