cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

mpa_add_unittest(
    NAME coreutils
    TARGET_SOURCES ut_coreutils.cpp
    LINK_LIBS mpacore gtest_main
    )

mpa_add_unittest(
    NAME mpanumber
    TARGET_SOURCES ut_mpanumber.cpp
    LINK_LIBS mpacore mpaerror gtest_main
    )
