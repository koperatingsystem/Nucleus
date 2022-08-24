# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.0)

project(kOS.Specific.riscv64)

find_program(MAKE_EXE NAMES gmake nmake make)

include(ExternalProject)

ExternalProject_Add(opensbi
        GIT_REPOSITORY https://github.com/riscv-software-src/opensbi.git
        GIT_TAG v1.1
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ${MAKE_EXE} PLATFORM=generic CROSS_COMPILE=riscv64-unknown-elf LLVM=1
        BUILD_IN_SOURCE true
)

ExternalProject_Get_Property(opensbi install_dir)
set(OPENSBI_INSTALL_DIR ${install_dir})

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/Shared/)

add_subdirectory(LKInterface)
add_subdirectory(Loader)
