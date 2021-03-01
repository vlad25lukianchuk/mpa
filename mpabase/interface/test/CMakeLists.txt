cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

mpa_add_unittest(
    NAME mpainteger
    TARGET_SOURCES ut_mpainteger.cpp
    LINK_LIBS mpa mpaerror gtest_main
    )
