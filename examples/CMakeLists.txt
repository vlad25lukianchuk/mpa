cmake_minimum_required(VERSION 3.15 FATAL_ERROR)

mpa_add_executable(
    NAME integer_addition
    TARGET_SOURCES integer_addition.cpp
    LINK_LIBS mpainterface
    )

mpa_add_executable(
    NAME integer_subtraction
    TARGET_SOURCES integer_subtraction.cpp
    LINK_LIBS mpainterface
    )

mpa_add_executable(
    NAME integer_multiplication
    TARGET_SOURCES integer_multiplication.cpp
    LINK_LIBS mpainterface
    )

mpa_add_executable(
    NAME integer_division
    TARGET_SOURCES integer_division.cpp
    LINK_LIBS mpainterface
    )

mpa_add_executable(
    NAME integer_reminder
    TARGET_SOURCES integer_reminder.cpp
    LINK_LIBS mpainterface
    )
