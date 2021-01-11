cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

mpa_add_unittest(
    NAME test_example
    TARGET_SOURCES main.cpp
    LINK_LIBS mpacore gtest_main
    )
