# Specify library and binary output directories
if(WIN32)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
else()
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
endif()

# Configure build type
# Set a default build type if none was specified
set(DEFAULT_BUILD_TYPE "Release")
if(EXISTS "${CMAKE_SOURCE_DIR}/.git")
    set(DEFAULT_BUILD_TYPE "Debug")
endif()

# No reason to set CMAKE_CONFIGURATION_TYPES if it is NOT a multiconfig generator
# No reason to set CMAKE_BUILD_TYPE if it is a multiconfig generator
get_property(isMultiConfig GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
if(isMultiConfig)
    set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Coverage" CACHE STRING "" FORCE)
else()
    if(NOT CMAKE_BUILD_TYPE)
        message(STATUS
            "Setting build type to '${DEFAULT_BUILD_TYPE}' as none was specified.")
        set(CMAKE_BUILD_TYPE "${DEFAULT_BUILD_TYPE}" CACHE STRING
            "Choose the type of build." FORCE)
    endif()
    # Set the possible values of build type for cmake-gui
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "Coverage")
endif()
