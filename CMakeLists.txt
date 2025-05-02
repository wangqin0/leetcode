cmake_minimum_required(VERSION 3.20)

# Set compiler to Clang if CC/CXX environment variables are not set
if(NOT DEFINED ENV{CC})
  set(CMAKE_C_COMPILER clang)
endif()
if(NOT DEFINED ENV{CXX})
  set(CMAKE_CXX_COMPILER clang++)
endif()

project(Leetcode
    VERSION 0.1.0
    DESCRIPTION "Leetcode solutions"
    LANGUAGES CXX)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(src)
