# add CTest, this will automatically creates a BUILD_TESTING option
include(CTest)

if(${BUILD_TESTING})
    # add google test to project
    # from https://github.com/google/googletest/blob/master/googletest/README.md

    # Download and unpack googletest at configure time
    configure_file(${MPA_ROOT_DIR}/external/googletest/CMakeLists.txt.in
        googletest-download/CMakeLists.txt)

    execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
      RESULT_VARIABLE result
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download)

    if(result)
        message(FATAL_ERROR "CMake step for googletest failed: ${result}")
    endif()

    execute_process(COMMAND ${CMAKE_COMMAND} --build .
      RESULT_VARIABLE result
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )

    if(result)
        message(FATAL_ERROR "Build step for googletest failed: ${result}")
    endif()

    # Prevent overriding the parent project's compiler/linker
    # settings on Windows
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    # Add googletest directly to our build. This defines
    # the gtest and gtest_main targets.
    add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
        ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
        EXCLUDE_FROM_ALL)

    # include tests
    add_subdirectory(${MPA_ROOT_DIR}/tests)

    if(${CMAKE_BUILD_TYPE} STREQUAL "Coverage")
        # enable coverage
        find_program(GCOV_PATH gcov)
        find_program(LCOV_PATH  NAMES lcov lcov.bat lcov.exe lcov.perl)
        find_program(GENHTML_PATH NAMES genhtml genhtml.perl genhtml.bat)

        if(NOT GCOV_PATH)
            message(FATAL_ERROR "gcov not found.")
        endif()

        # add coverage generation script
        configure_file(${MPA_ROOT_DIR}/scripts/generate_coverage.sh.in
            scripts/generate_coverage.sh @ONLY)
    endif()
endif()
