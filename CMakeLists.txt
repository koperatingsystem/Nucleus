# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.0)
project(kOS.Nucleus C)

set(CMAKE_C_STANDARD 99)

if (NOT CMAKE_TOOLCHAIN_FILE)
    message(FATAL_ERROR "To build kOS, you must use the kOS toolchain file")
endif ()

if (NOT ${CMAKE_GENERATOR} STREQUAL "Ninja" AND NOT ${CMAKE_GENERATOR} STREQUAL "Ninja Multi-Config")
    message(FATAL_ERROR "kOS requires using Ninja or Ninja Multi-Config as the generator.")
endif ()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/Shared")

add_subdirectory(libc)
add_subdirectory(ELFLoader)
add_subdirectory(LKInterface)
add_subdirectory(Kernel)
# TODO: Implement the 64 bit loader
add_subdirectory(Loader)

add_file_iso(${CMAKE_CURRENT_LIST_DIR}/Shared/grub.cfg boot/grub/)
