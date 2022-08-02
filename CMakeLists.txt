# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.0)

set(TARGET_ARCH "NOTSET" CACHE STRING "Target architecture")

if (TARGET_ARCH STREQUAL "NOTSET")
    message(FATAL_ERROR "You must set the target architecture")
endif()

set(CMAKE_TOOLCHAIN_FILE "Specific/${TARGET_ARCH}/kos-toolchain.cmake")

project(kOS.Nucleus C)

if (NOT CMAKE_TOOLCHAIN_FILE)
    message(FATAL_ERROR "To build kOS, you must use the kOS toolchain file")
endif ()

if (NOT ${CMAKE_GENERATOR} STREQUAL "Ninja" AND NOT ${CMAKE_GENERATOR} STREQUAL "Ninja Multi-Config")
    message(FATAL_ERROR "kOS requires using Ninja or Ninja Multi-Config as the generator.")
endif ()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/Shared")

add_subdirectory(Agnostic)
add_subdirectory(Specific)

