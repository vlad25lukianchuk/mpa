# Add CTest, this will automatically creates a BUILD_TESTING option
include(CTest)

if(${BUILD_TESTING})
    # Prevent overriding the parent project's compiler/linker
    # settings on Windows
    if(WIN32)
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    endif()

    # Add google test to project. This defines
    # the gtest and gtest_main targets.
    add_subdirectory(${MPA_ROOT_DIR}/external/googletest)

    if(${CMAKE_BUILD_TYPE} STREQUAL "Coverage")
        # Enable coverage
        find_program(GCOV_PATH gcov)
        find_program(LCOV_PATH  NAMES lcov lcov.bat lcov.exe lcov.perl)
        find_program(GENHTML_PATH NAMES genhtml genhtml.perl genhtml.bat)

        if(NOT GCOV_PATH)
            message(FATAL_ERROR "gcov not found.")
        endif()

        # Add coverage generation script
        configure_file(${MPA_ROOT_DIR}/scripts/generate_coverage.sh.in
            scripts/generate_coverage.sh @ONLY)
    endif()
endif()
