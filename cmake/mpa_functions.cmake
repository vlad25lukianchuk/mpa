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

    _internal_get_lib_info("${MPA_SHARED_LIB_NAME}" lib_name)

    add_library(${lib_name_full}
        SHARED ${MPA_SHARED_LIB_TARGET_SOURCES})

    if(NOT "${MPA_SHARED_LIB_PUBLIC_LINK_LIB}" STREQUAL "")
        target_link_libraries(${lib_name_full}
            PUBLIC ${MPA_SHARED_LIB_PUBLIC_LINK_LIB})
    endif()

    if(NOT "${MPA_SHARED_LIB_PRIVATE_LINK_LIB}" STREQUAL "")
        target_link_libraries(${lib_name_full}
            PRIVATE ${MPA_SHARED_LIB_PRIVATE_LINK_LIB})
    endif()

    if(NOT "${MPA_SHARED_LIB_PUBLIC_INCL}" STREQUAL "")
        target_include_directories(${lib_name_full}
            PUBLIC ${MPA_SHARED_LIB_PUBLIC_INCL})
    endif()

    if(NOT "${MPA_SHARED_LIB_PRIVATE_INCL}" STREQUAL "")
        target_include_directories(${lib_name_full}
            PRIVATE ${MPA_SHARED_LIB_PRIVATE_INCL})
    endif()

    target_compile_definitions(${lib_name_full}
        PRIVATE MPA_BUILD_${lib_name_upper}_LIB)

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

# Internal helper function to retrieve library information
# If target is 'core' and result is 'lib_name' than it defines:
# 'lib_name_full' - 'mpacore'
# 'lib_name_upper' - 'CORE'
# 'lib_name_lower' - 'core'
function(_internal_get_lib_info target result)
    set(lib_name "mpa${target}")
    set("${result}_full" "${lib_name}" PARENT_SCOPE)
    string(TOUPPER "${target}" upper)
    string(TOLOWER "${target}" lower)
    set("${result}_upper" "${upper}" PARENT_SCOPE)
    set("${result}_lower" "${lower}" PARENT_SCOPE)
endfunction()
