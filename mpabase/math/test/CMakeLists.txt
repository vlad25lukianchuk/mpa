cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

mpa_add_unittest(
    NAME addition
    TARGET_SOURCES ut_addition.cpp
    LINK_LIBS mpamath mpacore gtest_main
    )

mpa_add_unittest(
    NAME subtraction
    TARGET_SOURCES ut_subtraction.cpp
    LINK_LIBS mpamath mpacore gtest_main
    )

mpa_add_unittest(
    NAME multiplication
    TARGET_SOURCES ut_multiplication.cpp
    LINK_LIBS mpamath mpacore gtest_main
    )

mpa_add_unittest(
    NAME division
    TARGET_SOURCES ut_division.cpp
    LINK_LIBS mpamath mpacore mpaerror gtest_main
    )

mpa_add_unittest(
    NAME reminder
    TARGET_SOURCES ut_reminder.cpp
    LINK_LIBS mpamath mpacore mpaerror gtest_main
    )
