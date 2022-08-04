# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.0)

project(kOS.Loader LANGUAGES ASM C VERSION 1.0.0)

add_executable(kOS.Loader
        Sources/Bootstrap.S Sources/LoadKernel.c
        Sources/Main.c Includes/LoadKernel.h)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(kOS.Loader PRIVATE LOW_RES_FB)
endif()

target_compile_definitions(kOS.Loader PRIVATE VERSION=${PROJECT_VERSION})

target_compile_options(kOS.Loader PRIVATE ${SHARED_COMPILE_OPTIONS} -m32 -target i686-unknown-none)
target_include_directories(kOS.Loader PRIVATE Includes)

target_link_libraries(kOS.Loader PUBLIC kOS.libc.Loader kOS.LKI.32 kOS.LKI.Headers)
target_link_options(kOS.Loader PRIVATE -nostdlib -z max-page-size=0x1000)

add_target_output_iso(kOS.Loader boot)