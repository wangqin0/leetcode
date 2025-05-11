cmake_minimum_required(VERSION 3.30)

# Set compiler to Clang if CC/CXX environment variables are not set
if(NOT DEFINED ENV{CC})
  set(CMAKE_C_COMPILER clang)
endif()
if(NOT DEFINED ENV{CXX})
  set(CMAKE_CXX_COMPILER clang++)
endif()

if(APPLE)
  execute_process(
    COMMAND xcrun --sdk macosx --show-sdk-path
    OUTPUT_VARIABLE OSX_SDK_PATH
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )
  set(CMAKE_OSX_SYSROOT "${OSX_SDK_PATH}" CACHE STRING "Mac OS X SDK root" FORCE)
  message(STATUS "Using MacOSX SDK at ${CMAKE_OSX_SYSROOT}")
endif()

# On Linux, detect sysroot via compiler and set CMAKE_SYSROOT
if(UNIX AND NOT APPLE)
  execute_process(
    COMMAND "${CMAKE_C_COMPILER}" "--print-sysroot"
    OUTPUT_VARIABLE SYSROOT
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_QUIET
  )
  if(NOT "${SYSROOT}" STREQUAL "")
    set(CMAKE_SYSROOT "${SYSROOT}" CACHE STRING "System root for all languages" FORCE)
    set(CMAKE_CXX_SYSROOT "${SYSROOT}" CACHE STRING "C++ system root" FORCE)
    message(STATUS "Using sysroot at ${SYSROOT}")
  endif()
endif()

# On Windows, rely on default include paths; no sysroot override
if(WIN32)
  message(STATUS "Building on Windows; using default include paths")
endif()

# Ensure we're using a generator that supports C++20 modules
if(NOT CMAKE_GENERATOR MATCHES "Ninja")
  message(WARNING "Using generator: ${CMAKE_GENERATOR}. For C++20 modules support, Ninja, Ninja Multi-Config, or VS 17.4+ is recommended.")
endif()

project(Leetcode
    VERSION 0.1.0
    DESCRIPTION "Leetcode solutions"
    LANGUAGES CXX)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set C++ module scan settings
set(CMAKE_CXX_SCAN_FOR_MODULES ON)

# Set module output directory
set(CMAKE_CXX_MODULE_MAP_DIR "${CMAKE_BINARY_DIR}/modules")
set(CMAKE_CXX_MODULE_BMI_DIRECTORY "${CMAKE_BINARY_DIR}/modules")

add_subdirectory(src)