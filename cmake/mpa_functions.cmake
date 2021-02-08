# Function for adding shared library
# How to use:
# mpa_add_shared_library(
#                       NAME your_lib_name
#                       TARGET_SOURCES source1, source2, ...
#                       PUBLIC_LINK_LIB lib1, lib2, ...
#                       PUBLIC_INCL dir1, dir2, ...
# )
function(mpa_add_shared_library)
    set(options "")
    set(one_value_args NAME)
    set(multi_value_args TARGET_SOURCES PUBLIC_INCL PRIVATE_INCL
        PUBLIC_LINK_LIB PRIVATE_LINK_LIB)

    cmake_parse_arguments(
        MPA_SHARED_LIB
        "${options}"
        "${one_value_args}"
        "${multi_value_args}"
        "${ARGN}"
        )

    if("${MPA_SHARED_LIB_NAME}" STREQUAL "")
        message(FATAL_ERROR "Library name is not set")
    endif()

    if("${MPA_SHARED_LIB_TARGET_SOURCES}" STREQUAL "")
        message(FATAL_ERROR "Library sources are not set")
    endif()

    add_library(${MPA_SHARED_LIB_NAME}
        SHARED ${MPA_SHARED_LIB_TARGET_SOURCES})

    if(NOT "${MPA_SHARED_LIB_PUBLIC_LINK_LIB}" STREQUAL "")
        target_link_libraries(${MPA_SHARED_LIB_NAME}
            PUBLIC ${MPA_SHARED_LIB_PUBLIC_LINK_LIB})
    endif()

    if(NOT "${MPA_SHARED_LIB_PRIVATE_LINK_LIB}" STREQUAL "")
        target_link_libraries(${MPA_SHARED_LIB_NAME}
            PRIVATE ${MPA_SHARED_LIB_PRIVATE_LINK_LIB})
    endif()

    if(NOT "${MPA_SHARED_LIB_PUBLIC_INCL}" STREQUAL "")
        target_include_directories(${MPA_SHARED_LIB_NAME}
            PUBLIC ${MPA_SHARED_LIB_PUBLIC_INCL})
    endif()

    if(NOT "${MPA_SHARED_LIB_PRIVATE_INCL}" STREQUAL "")
        target_include_directories(${MPA_SHARED_LIB_NAME}
            PRIVATE ${MPA_SHARED_LIB_PRIVATE_INCL})
    endif()

endfunction()

# Function for adding executable
# How to use:
# mpa_add_executable(
#                   NAME your_exe_name
#                   TARGET_SOURCES source1, source2, ...
#                   LINK_LIBS lib1, lib2, ...
#                   INCLUDE_DIRS dir1, dir2, ...
# Note: we link libraries and include directories privately by default
# )
function(mpa_add_executable)
    set(options "")
    set(one_value_args NAME)
    set(multi_value_args TARGET_SOURCES LINK_LIBS INCLUDE_DIRS)

    cmake_parse_arguments(
        MPA_EXE
        "${options}"
        "${one_value_args}"
        "${multi_value_args}"
        "${ARGN}"
        )

    if("${MPA_EXE_NAME}" STREQUAL "")
        message(FATAL_ERROR "Executable name is not set")
    endif()

    add_executable(${MPA_EXE_NAME} ${MPA_EXE_TARGET_SOURCES})

    if(NOT "${MPA_EXE_LINK_LIBS}" STREQUAL "")
        target_link_libraries(${MPA_EXE_NAME}
            PRIVATE ${MPA_EXE_LINK_LIBS})
    endif()

    if(NOT "${MPA_EXE_INCLUDE_DIRS}" STREQUAL "")
        target_include_directories(${MPA_EXE_NAME}
            PRIVATE ${MPA_EXE_INCLUDE_DIRS})
    endif()

endfunction()

# Function for adding unit test
# How to use:
# mpa_add_unittest(
#                 NAME your_test_name
#                 TARGET_SOURCES source1, source2, ...
#                 LINK_LIBS lib1, lib2, ...
#                 INCLUDE_DIRS dir1, dir2, ...
# )
function(mpa_add_unittest)
    set(options "")
    set(one_value_args NAME)
    set(multi_value_args TARGET_SOURCES LINK_LIBS INCLUDE_DIRS)

    cmake_parse_arguments(
        MPA_UT
        "${options}"
        "${one_value_args}"
        "${multi_value_args}"
        "${ARGN}"
        )

    mpa_add_executable(
        NAME "ut_${MPA_UT_NAME}"
        TARGET_SOURCES ${MPA_UT_TARGET_SOURCES}
        LINK_LIBS ${MPA_UT_LINK_LIBS}
        INCLUDE_DIRS ${MPA_UT_INCLUDE_DIRS}
        )

    set(TEST_NAME "mpa_${MPA_UT_NAME}")

    add_test(
        NAME ${TEST_NAME}
        COMMAND "ut_${MPA_UT_NAME}"
        )

endfunction()
