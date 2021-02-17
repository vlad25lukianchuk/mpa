cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

mpa_add_unittest(
    NAME mpalog
    TARGET_SOURCES ut_mpalog.cpp
    LINK_LIBS mpalog gtest_main
    )
